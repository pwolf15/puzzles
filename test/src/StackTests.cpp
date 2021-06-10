#include <iostream>

#include "LinkedLists.hpp"
#include "Stacks.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Stacks)
{
 
};

TEST(Stacks, PrintLinkedListInReverse)
{
    std::shared_ptr<ListNodeEPI<int>> l1 = createList({ 3, 1, 4 });
    PrintLinkedListInReverse(l1);
};

TEST(Stacks, StackWithMax)
{
    StackWithMax s;
    for (int i = 0; i < 10; ++i)
    {
        s.Push(i);
        s.Push(i);
        s.Push(i);
    }

    std::vector<int> expected = { 9, 9, 9, 8, 8 };
    for (int i = 0; i < 5; ++i)
    {
        int m = s.Max();
        CHECK_EQUAL(expected[i], m);
        s.Pop();
    }

    StackWithMax_EPI s2;
    for (int i = 0; i < 10; ++i)
    {
        s2.Push(i);
        s2.Push(i);
        s2.Push(i);
    }

    expected = { 9, 9, 9, 8, 8 };
    for (int i = 0; i < 5; ++i)
    {
        int m = s2.Max();
        CHECK_EQUAL(expected[i], m);
        s2.Pop();
    }
};

TEST(Stacks, MyStack)
{
    MyStack2 myStack;
    myStack.push(1);
    myStack.push(2);
    CHECK_EQUAL(2, myStack.top());
    CHECK_EQUAL(2, myStack.pop());
    CHECK_EQUAL(1, myStack.pop());
    CHECK(myStack.empty());
};

TEST(Stacks, Clumsy)
{
    CHECK_EQUAL(7, clumsy(4));
    CHECK_EQUAL(12, clumsy(10));
    CHECK_EQUAL(12, clumsy(10));
};