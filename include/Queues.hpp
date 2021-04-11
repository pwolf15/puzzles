#include <stack>
#include <iostream>

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        front = -1;
    }
    
    // time complexity: O(1)
    // space complexity: O(n)
    /** Push element x to the back of queue. */
    void push(int x) {
        m_a.push(x);

        if (m_a.size() == 1)
        {
            front = x;
        }
    }
    
    // time complexity: O(n)
    // space complexity: O(n)
    /** Removes the element from in front of queue and returns that element. */
    int pop() {

        int oldFront = front;
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

        if (!m_b.empty())
            front = m_b.top();

        while (!m_b.empty())
        {
            m_a.push(m_b.top());
            m_b.pop();
        }

        return oldFront;
    }
    
    // time complexity: O(1)
    // space complexity: O(n)
    /** Get the front element. */
    int peek() {
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