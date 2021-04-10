#ifndef STACKS_HPP
#define STACKS_HPP

#include "LinkedLists.hpp"

#include <stack>
#include <map>
#include <queue>

void PrintLinkedListInReverse(std::shared_ptr<ListNodeEPI<int>> head);

// space complexity: O(n)
// time complexity: O(1) max, O(log n) pop and push
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

// space complexity: O(n)
// time complexity: O(1) max, pop, push
class StackWithMax_EPI
{
public: 
    bool Empty() const {
        return std::empty(element_with_cached_max_);
    }

    int Max() const {
        return element_with_cached_max_.top().max;
    }

    int Pop() {
        int pop_element = element_with_cached_max_.top().element;
        element_with_cached_max_.pop();
        return pop_element;
    }

    void Push(int x) {
        element_with_cached_max_.emplace(
            ElementWithCachedMax{x, std::max(x, Empty() ? x : Max())});
    }
private:
    struct ElementWithCachedMax {
        int element, max;
    };
    std::stack<ElementWithCachedMax> element_with_cached_max_;
};


class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        m_a.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {

        while (true)
        {
            if (m_a.empty())
            {
                break;
            }

            int cur = m_a.front();
            m_a.pop();

            if (m_a.empty())
            {
                std::swap(m_a, m_b);
                return cur;
            }
            else
            {
                m_b.push(cur);
            }
        }

        return -1;
    }
    
    /** Get the top element. */
    int top() {

        while (true)
        {
            if (m_a.empty())
            {
                break;
            }

            int cur = m_a.front();
            m_a.pop();

            if (m_a.empty())
            {
                m_b.push(cur);
                std::swap(m_a, m_b);
                return cur;
            }
            else
            {
                m_b.push(cur);
            }
        }

        return -1;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return m_a.empty();
    }

private:
    std::queue<int> m_a;
    std::queue<int> m_b;
};

#endif // STACKS_HPP