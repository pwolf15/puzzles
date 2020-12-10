#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::vector<std::string> split(std::string s, std::regex r)
{
    using namespace std;
  vector<string> splits;
  smatch m; // <-- need a match object

  while (regex_search(s, m, r))  // <-- use it here to get the match
  {
    int split_on = m.position(); // <-- use the match position
    splits.push_back(s.substr(0, split_on));
    s = s.substr(split_on + m.length()); // <-- also, skip the whole match
  }

  if(!s.empty()) {
    splits.push_back(s); // and there may be one last token at the end
  }

  return splits;
}

void addNewBag(std::unordered_map<std::string, std::vector<std::string>>& bags, std::string rule)
{
    std::regex regEx("bag");
    std::vector<std::string> results = split(rule, regEx);
    trim(results[0]);
    bags[results[0]] = {};

    std::vector<std::string> colors;

    for (size_t i = 1; i < results.size() - 1; ++i)
    {
        std::string color;
        int numSpaces = 0;
        std::string result = results[i];
        for (size_t j = result.size() - 1; j >= 0; j--)
        {
            if (result[j] == ' ')
            {
                numSpaces++;
            }

            if (numSpaces > 2)
            {
                break;
            }
            color += result[j];
        }

        std::reverse(color.begin(), color.end());
        trim(color);

        colors.push_back(color);
    }

    bags[results[0]] = colors;
}

bool bagContainsGold(const std::string& bag, std::unordered_set<std::string>& bagsWithGold)
{
    if (bag == "shiny gold" || bagContainsGold(bag, bagsWithGold))
    {
        return true;
    }

    return false;
}

int computeNumBags(std::string filename)
{
    std::string line;
    int numBags = 0;
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return numBags;
    }

    std::vector<std::string> lines;
    std::unordered_map<std::string, std::vector<std::string>> bags;
    std::unordered_set<std::string> bagsWithGold;
    bagsWithGold.insert("shiny gold");
    int prevNumBags = 0;
    int curNumBags = 0;

    while (getline(infile, line))
    {
        lines.push_back(line);
        addNewBag(bags, line);
    }

    while (true)
    {

        for (auto bag: bags)
        {
            for (auto subBag: bag.second)
            {
                if (bagsWithGold.contains(subBag))
                {
                    bagsWithGold.insert(bag.first);
                }
            }
        }

        curNumBags = bagsWithGold.size();

        if (prevNumBags == curNumBags)
        {
            break;
        }

        prevNumBags = curNumBags;
    }

    std::cout << "Num bags: " << bags.size() << std::endl;
    std::cout << "Num gold bags: " << curNumBags - 1<< std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return numBags;
}

int main()
{ 
    computeNumBags("../day7.txt");
    return 0;
}