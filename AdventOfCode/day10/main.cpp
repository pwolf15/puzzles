#include <algorithm>
#include <fstream>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

std::vector<std::string> get_lines(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return lines;
    }

    std::string line;
    while (getline(infile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day10.txt");
    std::vector<int> joltages;

    joltages.push_back(0);
    std::transform(lines.begin(), lines.end(), std::back_inserter(joltages), [](std::string line) {
        return std::stoi(line);
    });
    std::sort(joltages.begin(), joltages.end());
    joltages.push_back(joltages[joltages.size() - 1] + 3);

    int diffOne     = 0;
    int diffThree   = 0;

    for (int i = 1; i < joltages.size(); ++i)
    {
        if ((joltages[i] - joltages[i - 1]) == 1)
        {
            diffOne++;
        }
        else if ((joltages[i] - joltages[i - 1]) == 3)
        {
            diffThree++;
        }
    }

    int product = diffOne * diffThree;

    std::cout << "Diff one: " << diffOne << std::endl;
    std::cout << "Diff three: " << diffThree << std::endl;
    std::cout << "Product: " << product << std::endl;

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num joltages: " << joltages.size() << std::endl;

    return 0;
}