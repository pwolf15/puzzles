#ifndef STACKS_HPP
#define STACKS_HPP

#include "LinkedLists.hpp"

#include <stack>
#include <map>

void PrintLinkedListInReverse(std::shared_ptr<ListNodeEPI<int>> head);

class StackWithMax
{
public: 
    bool Empty() const {
        return s.empty();
    }

    int Max() const {
        return m.rbegin()->first;
    }

    int Pop() {
        if (s.empty())
        {
            return -1;
        }
        int v = s.top();
        m.find(v)->second--;
        if (m.find(v)->second == 0)
        {
            m.erase(v);
        }
        s.pop();
        return v;
    }

    void Push(int x) {
        s.push(x);

        if (m.find(x) == m.end())
        {
            m[x] = 1;
        }
        else
        {
            m.find(x)->second++;
        }
    }
private:
    std::stack<int> s;
    std::map<int, int> m;
};

#endif // STACKS_HPP