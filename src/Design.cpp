#include "Design.hpp"

#include <random>
#include <ctime>
#include <set>
#include <iostream>

ShuffledArray::ShuffledArray(std::vector<int> &nums): m_nums(nums)
{
    srand(time(NULL));

    for (auto num: nums)
    {
        m_nums_backup.push_back(num);
    }
}

std::vector<int> ShuffledArray::reset()
{
    size_t i = 0;
    for (auto num: m_nums_backup)
    {
        m_nums[i] = m_nums_backup[i];
        i++;
    }

    return m_nums;
}

std::vector<int> ShuffledArray::shuffle()
{
    std::set<int> randomized;
    std::vector<int> randomizedVec;
    while (randomized.size() < m_nums.size())
    {
        size_t index = rand() % m_nums.size();
        if (randomized.find(index) == randomized.end())
        {
            randomized.insert(index);
            randomizedVec.push_back(index);
        }
    }

    std::vector<int> numsRandomized;
    auto i = 0;
    for (auto index: randomizedVec)
    {
        m_nums[i] = m_nums_backup[index];
        i++;
    }

    return m_nums;
}