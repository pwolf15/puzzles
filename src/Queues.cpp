#include "Queues.hpp"

// time complexity: O(n)
// space complexity: O(n)
int countStudents_PW1(std::vector<int>& students, std::vector<int>& sandwiches)
{
    std::queue<int> studQueue;
    std::queue<int> sandQueue;

    for (auto s: students)
    {
        studQueue.push(s);
    }

    for (auto s: sandwiches)
    {
        sandQueue.push(s);
    }

    int turnsSincePop = 0;
    while (!studQueue.empty() && !sandQueue.empty() && turnsSincePop != sandQueue.size())
    {
        if (sandQueue.front() == studQueue.front())
        {
            sandQueue.pop();
            studQueue.pop();
            turnsSincePop = 0;
        }
        else if (sandQueue.front() != studQueue.front())
        {
            studQueue.push(studQueue.front());
            studQueue.pop();
            ++turnsSincePop;
        }
    }

    return studQueue.size();
}

// time complexity: O(n)
// space complexity: O(1)
int countStudents_PW2(std::vector<int>& students, std::vector<int>& sandwiches)
{
    std::vector<int> count = {0, 0};
    int n = students.size();
    int k;
    for (int s: students)
    {
        count[s]++;
    }
    for (k = 0; k < n && count[sandwiches[k]] > 0; ++k)
    {
        count[sandwiches[k]]--;
    }
    return n - k;
}

int countStudents(std::vector<int>& students, std::vector<int>& sandwiches)
{
    return countStudents_PW2(students, sandwiches);
}