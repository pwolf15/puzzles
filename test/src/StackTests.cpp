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
};