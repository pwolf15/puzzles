#include "Queues.hpp"

int countStudents(std::vector<int>& students, std::vector<int>& sandwiches)
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