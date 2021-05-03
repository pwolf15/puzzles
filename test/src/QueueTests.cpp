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