#include <stack>
#include <iostream>

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        m_a.push(x);

        if (m_a.size() == 1)
        {
            front = x;
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {

        while (!m_a.empty())
        {
            front = m_a.top();
            m_a.pop();

            if (m_a.empty())
            {
                break;
            }
            else
            {
                m_b.push(front);
            }
        }

        while (!m_b.empty())
        {
            m_a.push(m_b.top());
            m_b.pop();
        }

        return front;
    }
    
    /** Get the front element. */
    int peek() {
        
        while (!m_a.empty())
        {
            front = m_a.top();
            m_a.pop();

            if (m_a.empty())
            {
                m_b.push(front);
                break;
            }
            else
            {
                m_b.push(front);
            }
        }

        while (!m_b.empty())
        {
            m_a.push(m_b.top());
            m_b.pop();
        }

        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return m_a.empty();
    }

private:
    std::stack<int> m_a;
    std::stack<int> m_b;
    int front = 0;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */