#include "Queues.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Queues)
{
 
};

TEST(Queues, MyQueue)
{
    // MyQueue2 myQueue;
    // myQueue.push(1);
    // myQueue.push(2);
    // myQueue.push(3);
    // CHECK_EQUAL(1, myQueue.peek());
    // CHECK_EQUAL(1, myQueue.pop());
    // CHECK_EQUAL(2, myQueue.pop());
    // CHECK_EQUAL(3, myQueue.pop());
    // CHECK(myQueue.empty());

    // MyQueue2 myQueue2;
    // myQueue2.push(1);
    // myQueue2.push(2);
    // myQueue2.push(3);
    // CHECK_EQUAL(1, myQueue2.pop());
    // CHECK_EQUAL(2, myQueue2.peek());
};

TEST(Queues, CountStudents)
{
    std::vector<int> students = { 1,1,0,0 };
    std::vector<int> sandwiches = { 0,1,0,1 };
    CHECK_EQUAL(0, countStudents(students, sandwiches));

    students = { 1,1,1,0,0,1 };
    sandwiches = { 1,0,0,0,1,1 };
    CHECK_EQUAL(3, countStudents(students, sandwiches));
};

TEST(Queues, CircularQueue_EPI)
{
    CircularQueue_EPI q(0);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    CHECK_EQUAL(3, q.Size());

    CHECK_EQUAL(1, q.Dequeue());
    CHECK_EQUAL(2, q.Dequeue());
    CHECK_EQUAL(3, q.Dequeue());

    CHECK_EQUAL(0, q.Size());

    CircularQueue_EPI q2(100);
    for (int i = 0; i < 1000; ++i)
    {
        q2.Enqueue(i);
    }

    for (int i = 0; i < 1000; ++i)
    {
        CHECK_EQUAL(i, q2.Dequeue());
    }

    CircularQueue_EPI q3(10);
    for (int i = 0; i < 10; ++i)
    {
        q3.Enqueue(i);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        CHECK_EQUAL(i, q3.Dequeue());
    }

    for (int i = 10; i < 15; ++i)
    {
        q3.Enqueue(i);
    }

    for (int i = 5; i < 10; ++i)
    {
        CHECK_EQUAL(i, q3.Dequeue());
    }   
};

TEST(Queues, CircularQueue_EPI2)
{
    CircularQueue_EPI2 q(0);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    CHECK_EQUAL(3, q.Size());

    CHECK_EQUAL(1, q.Dequeue());
    CHECK_EQUAL(2, q.Dequeue());
    CHECK_EQUAL(3, q.Dequeue());

    CHECK_EQUAL(0, q.Size());

    CircularQueue_EPI2 q2(100);
    for (int i = 0; i < 1000; ++i)
    {
        q2.Enqueue(i);
    }

    for (int i = 0; i < 1000; ++i)
    {
        CHECK_EQUAL(i, q2.Dequeue());
    }

    CircularQueue_EPI2 q3(10);
    for (int i = 0; i < 10; ++i)
    {
        q3.Enqueue(i);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        CHECK_EQUAL(i, q3.Dequeue());
    }

    for (int i = 10; i < 15; ++i)
    {
        q3.Enqueue(i);
    }

    for (int i = 5; i < 10; ++i)
    {
        CHECK_EQUAL(i, q3.Dequeue());
    }   
};

TEST(Queues, CircularQueue_LC)
{
    CircularQueue_LC q5(2);
    q5.enQueue(1);  // 1,_
    q5.enQueue(2);  // 1,2
    CHECK_EQUAL(1, q5.Front());   // _,3
    q5.deQueue();
    CHECK_EQUAL(2, q5.Front());   // _,_
    q5.deQueue();
    q5.enQueue(3);
    CHECK_EQUAL(3, q5.Front()); 
    q5.deQueue();
    q5.enQueue(3);
    CHECK_EQUAL(3, q5.Front()); 
    q5.deQueue();
    q5.enQueue(3);
    CHECK_EQUAL(3, q5.Front()); 
    q5.deQueue();
    CHECK_EQUAL(-1, q5.Front());   
}