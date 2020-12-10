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

void addNewBag(std::unordered_map<std::string, std::vector<std::string>>& bags, std::unordered_map<std::string, std::vector<int>>& bagSubtotals, std::unordered_map<std::string, int>& bagCounts, std::string rule)
{
    std::regex regEx("bag");
    std::vector<std::string> results = split(rule, regEx);
    trim(results[0]);
    bags[results[0]] = {};

    std::vector<std::string> colors;
    std::vector<int> counts;

    if (rule.find("no other bags") != std::string::npos)
    {
        std::cout << results[0] << ": no other bags" << std::endl;
        bagCounts[results[0]] = 0;
        return;
    }

    for (size_t i = 1; i < results.size() - 1; ++i)
    {
        std::string color;
        int numSpaces = 0;
        std::string result = results[i];
        std::string bagCount;

        for (size_t j = result.size() - 1; j >= 0; j--)
        {
            if (result[j] == ' ')
            {
                numSpaces++;
            }

            if (numSpaces > 3)
            {  
                break;
            }
            else if (numSpaces > 2)
            {
                bagCount = result[j];
            }
            else
            {
                color += result[j];
            }
        }

        counts.push_back(std::stoi(bagCount));

        std::reverse(color.begin(), color.end());
        trim(color);

        colors.push_back(color);
    }

    std::cout << results[0] << ": ";
    for (size_t i = 0; i < counts.size(); ++i)
    {
        std::cout << counts[i] << " " << colors[i] << " | ";
    }

    bagSubtotals[results[0]] = counts;

    std::cout << std::endl;

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
    std::unordered_map<std::string, std::vector<int>> bagSubtotals;
    std::unordered_map<std::string, int> bagCounts;
    std::unordered_set<std::string> bagsWithGold;
    bagsWithGold.insert("shiny gold");
    int prevNumBags = 0;
    int curNumBags = 0;

    while (getline(infile, line))
    {
        lines.push_back(line);
        addNewBag(bags, bagSubtotals, bagCounts, line);
    }

    // while (true)
    // {

    //     for (auto bag: bags)
    //     {
    //         for (auto subBag: bag.second)
    //         {
    //             if (bagsWithGold.contains(subBag))
    //             {
    //                 bagsWithGold.insert(bag.first);
    //             }
    //         }
    //     }

    //     curNumBags = bagsWithGold.size();

    //     if (prevNumBags == curNumBags)
    //     {
    //         break;
    //     }

    //     prevNumBags = curNumBags;
    // }

    while (true)
    {
        for (auto bag: bags)
        {
            bool foundAll = true;
            int count = 0;
            size_t i = 0;
            for (auto subBag: bag.second)
            {
                if (bagCounts.find(subBag) == bagCounts.end())
                {
                    foundAll = false;
                    break;
                }
                else
                {
                    std::vector<int> counts = bagSubtotals.find(bag.first)->second;
                    count += counts[i++] * (bagCounts[subBag] + 1);
                    std::cout << "count: " << bagCounts[subBag] << std::endl;
                }
            }

            std::cout << "i: " << i << std::endl;

            if (foundAll)
            {
                std::cout << "Found all: " << std::endl;
                bagCounts[bag.first] = count;
            }
        }

        if (bags.size() == bagCounts.size())
        {
            break;
        }
    }

    std::cout << "Bag counts size: " << bagCounts.size() << std::endl;
    std::cout << "Bag total: " << bagCounts["shiny gold"] << std::endl;

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