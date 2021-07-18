#include <stack>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

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

class MyQueue2 {
public:
    /** Initialize your data structure here. */
    MyQueue2() {
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

        int sz = m_a.size();
        int i = 0;
        while (i <= sz)
        {
            front = m_a.top();
            m_a.pop();
            m_a.push(front);
            i++;
        }

        int oldFront = front;
        if (!m_a.empty())
            oldFront = m_a.top();
            m_a.pop();

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

int countStudents(std::vector<int>& students, std::vector<int>& sandwiches);

class CircularQueue_EPI
{
    public:
        CircularQueue_EPI(std::size_t capacity): 
            m_data(capacity),
            m_start(0),
            m_end(0),
            m_num_elements(0)
        {
            // cases
            // 1. normal: start < end
            // 2. wraparound
            // 3. exhausted capacity
            if (!capacity)
            {
                // resize (exhausted current capacity)
                m_data.resize((m_end + 1)*2);
            }
        }

        void Enqueue(int k)
        {
            m_data[m_end++] = k;
            m_num_elements++;

            if (m_num_elements >= m_data.size())
            {
                // exceeded size
                m_data.resize(m_data.size() * 2);

                // shift elements
                std::vector<int> new_data(m_data.size() * 2);
                
                if (m_start > m_end)
                {
                    for (int i = m_start; i < m_data.size(); ++i)
                    {
                        new_data.push_back(m_data[i]);
                    }
                    for (int i = 0; i <= m_end; ++i)
                    {
                        new_data.push_back(m_data[i]);
                    }

                    std::swap(m_data, new_data);
                }
                else
                {
                    for (int i = 0; i < m_data.size(); ++i)
                    {
                        new_data[i] = m_data[i];
                    }
                }

                m_start = 0;
                m_end = m_num_elements;
            }
            else if (m_end >= m_data.size())
            {
                // wraparound
                m_end = 0;
            }
        }

        int Dequeue()
        {
            int retVal = -1;
            if (m_num_elements <= 0)
            {
                // do nothing
            }
            else 
            {
                m_num_elements--;
                retVal = m_data[m_start++];
            }

            if (m_num_elements == 0)
            {
                m_start = m_end = 0;
            }
            else if (m_num_elements && m_start == m_data.size())
            {
                // wraparound
                m_start = 0;
            }

            return retVal;
        }

        int Size() const
        {
            return m_num_elements;
        }
    
    private:
        std::vector<int> m_data;
        int m_start, m_end, m_num_elements;
};

class CircularQueue_EPI2
{
    public:
        explicit CircularQueue_EPI2(std::size_t capacity): 
            entries_(capacity)
        {
            // added this to protect against zero-valued capacity
            if (num_queue_elements == std::size(entries_))
            {
                entries_.resize((std::size(entries_) + 1) * kScaleFactor);
            }
        }

        void Enqueue(int x)
        {
            if (num_queue_elements == std::size(entries_)) // Needs to resize.
            {
                // Make the queue elements appear consecutively
                std::rotate(std::begin(entries_), std::begin(entries_) + head_, std::end(entries_));
                head_ = 0, tail_ = num_queue_elements; // Resets head and tail;
                entries_.resize(std::size(entries_) * kScaleFactor);
            }

            entries_[tail_] = x;
            tail_ = (tail_ + 1) % std::size(entries_), ++num_queue_elements;
        }

        int Dequeue() 
        {
            --num_queue_elements;
            int result = entries_[head_];
            head_ = (head_ + 1) % std::size(entries_);
            return result;
        }

        int Size() const
        {
            return num_queue_elements;
        }
    
    private:
        const int kScaleFactor = 2;
        int head_ = 0, tail_ = 0, num_queue_elements = 0;
        std::vector<int> entries_;
};

class CircularQueue_LC
{
    public:
        CircularQueue_LC(std::size_t capacity): 
            m_data(capacity),
            m_start(0),
            m_end(0),
            m_num_elements(0)
        {
            // cases
            // 1. normal: start < end
            // 2. wraparound
            // 3. exhausted capacity
            if (!capacity)
            {
                // resize (exhausted current capacity)
                m_data.resize((m_end + 1)*2);
            }
        }


        int Front()
        {
            if (!m_num_elements)
            {
                return -1;
            }
            return m_data[m_start];
        }

        int Rear()
        {
            return m_data[m_end-1];
        }

        bool isEmpty()
        {
            return !m_num_elements;
        }

        bool isFull()
        {
            return m_num_elements == m_data.size();
        }

        void Enqueue(int k)
        {
            m_data[m_end++] = k;
            m_num_elements++;

            std::cout << "Num elements: " << m_num_elements << std::endl;

            if (m_num_elements >= m_data.size())
            {
                std::cout << "Resize!" << std::endl;

                // exceeded size
                m_data.resize(m_data.size() * 2);

                // shift elements
                std::vector<int> new_data(m_data.size() * 2);
                
                if (m_start > m_end)
                {
                    for (int i = m_start; i < m_data.size(); ++i)
                    {
                        new_data.push_back(m_data[i]);
                    }
                    for (int i = 0; i <= m_end; ++i)
                    {
                        new_data.push_back(m_data[i]);
                    }

                    std::swap(m_data, new_data);
                }
                else
                {
                    for (int i = 0; i < m_data.size(); ++i)
                    {
                        new_data[i] = m_data[i];
                    }
                }

                m_start = 0;
                m_end = m_num_elements;
            }
            else if (m_end >= m_data.size())
            {
                // wraparound
                m_end = 0;
            }

            std::cout << "Enqueue, Start: " << m_start << ", end: " << m_end << std::endl;
        }

        int Dequeue()
        {
            int retVal = -1;
            if (m_num_elements <= 0)
            {
                // do nothing
            }
            else 
            {
                m_num_elements--;
                retVal = m_data[m_start++];
            }

            if (m_num_elements == 0)
            {
                m_start = m_end = 0;
            }
            else if (m_num_elements && m_start == m_data.size())
            {
                // wraparound
                m_start = 0;
            }

            std::cout << "Dequeue, start: " << m_start << ", end: " << m_end << std::endl;

            return retVal;
        }

        int Size() const
        {
            return std::abs(m_end - m_start);
        }
    
    private:
        std::vector<int> m_data;
        int m_start, m_end, m_num_elements;
};