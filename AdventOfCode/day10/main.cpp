#include <algorithm>
#include <fstream>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

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

std::unordered_map<int, long long> cache;

long long get_good_results(std::vector<int> arr, int idx, std::vector<int> indices)
{
    long long good = 0;

    if (idx + 1 >= arr.size())
    {
        // for (auto i: indices)
        // {
        //     std::cout << arr[i] << ",";
        // }
        std::cout << "\n";
        return true;
    }

    for (int i = idx + 1; i < arr.size(); ++i)
    {
        int diff = arr[i] - arr[idx];
        if (diff >= 1 && diff <= 3)
        {
            std::vector<int> indices2;
            for (auto i: indices)
            {
                indices2.push_back(i);
            }
            indices2.push_back(i);
           
            long long results = 0;
            if (cache.find(i) == cache.end())
            {
                results = get_good_results(arr, i, indices2);
                cache[i] = results;
            }
            else
            {
                /* code */
                results = cache.find(i)->second;
            }
            
            good += results;
        }
    }

    return good;
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

    std::vector<int> arr = joltages;
    std::vector<int> indices = { 0 };
    long long good_results = get_good_results(arr, 0, indices);
    std::cout << "Good results: " << good_results << std::endl;

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num joltages: " << joltages.size() << std::endl;

    return 0;
}