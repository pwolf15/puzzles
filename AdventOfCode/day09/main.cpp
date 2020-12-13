#include <algorithm>
#include <fstream>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <boost/circular_buffer.hpp>
#include <queue>
#include <set>

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
    std::vector<std::string> lines = get_lines("../day09.txt");
    std::vector<long long> nums;

    std::transform(lines.begin(), lines.end(), std::back_inserter(nums), [](std::string line) {
        return std::stoll(line);
    });

    boost::circular_buffer<int> cb(25);

    //
    long long invalidSeqNum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i < 25)
        {
            cb.push_back(nums[i]);
        }
        else
        {
            bool foundMatch = false;
            for (int j = 0; j < cb.size() - 1; j++)
            {
                for (int k = j + 1; k < cb.size(); k++)
                {
                    if (cb[j] + cb[k] == nums [i])
                    {
                        foundMatch = true;
                        break;
                    }
                }
            }

            if (!foundMatch)
            {
                invalidSeqNum = nums[i];
                break;
            }
            else
            {
                cb.push_back(nums[i]);
            }
            
        }  
    }

    cb.clear();
    boost::circular_buffer<long long> cb2(1000);

    auto get_sum = [](boost::circular_buffer<long long> b) {
        
        long long sum = 0;
        for (auto j = b.begin(); j != b.end(); ++j)
        {
            sum += *j;
        }

        return sum;
    };

    bool foundSum = false;
    for (int i = 0; i < nums.size(); ++i)
    {
        cb2.push_back(nums[i]);


        long long sum = get_sum(cb2);
        if (sum > invalidSeqNum)
        {
            while (sum > invalidSeqNum)
            {
                cb2.pop_front();
                sum = get_sum(cb2);
            }
        }

        if (sum == invalidSeqNum)
        {
            std::cout << "Found sum" << std::endl;
            foundSum = true;
            break;
        }  
    }

    if (foundSum)
    {
        std::vector<long long> seq;
        for (auto j = cb2.begin(); j != cb2.end(); ++j)
        {
            seq.push_back(*j);
        }

        std::sort(seq.begin(), seq.end());

        std::cout << "first: " << seq[0] << std::endl;
        std::cout << "last: " << seq[seq.size() - 1] << std::endl;
        std::cout << "sum: " << seq[0] + seq[seq.size() - 1] << std::endl;
    }

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num nums: " << nums.size() << std::endl;
    std::cout << "Invalid seq num: " << invalidSeqNum << std::endl;

    return 0;
}