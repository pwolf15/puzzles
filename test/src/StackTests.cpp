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


TEST(Stacks, Evaluate)
{
    CHECK_EQUAL(15, Evaluate("3,4,+,2,*,1,+"));
    CHECK_EQUAL(1729, Evaluate("1729"));
    CHECK_EQUAL(-3, Evaluate("-641,6,/,28,/"));
};

TEST(Stacks, EvalRPN)
{
    std::vector<std::string> tokens = { "3","4","+","2","*","1","+"};
    CHECK_EQUAL(15, evalRPN(tokens));

    tokens = { "2","1","+","3","*" };
    CHECK_EQUAL(9, evalRPN(tokens));

    tokens = { "4","13","5","/","+" };
    CHECK_EQUAL(6, evalRPN(tokens));

    tokens = { "4","13","5","/","+" };
    CHECK_EQUAL(6, evalRPN(tokens));

    tokens = { "10","6","9","3","+","-11","*","/","*","17","+","5","+" };
    CHECK_EQUAL(22, evalRPN(tokens));
};

TEST(Stacks, IsWellFormed)
{
    CHECK(isWellFormed("([]){()}"));
    CHECK(isWellFormed("[()[]{()()}]"));
    CHECK(!isWellFormed("{)"));
    CHECK(!isWellFormed("{(})"));   
    CHECK(!isWellFormed("[()[]{()()")); 
}

TEST(Stacks, ShortestEquivalentPath)
{
    CHECK_EQUAL("/usr/bin/gcc", ShortestEquivalentPath("/usr/lib/../bin/gcc"));
    CHECK_EQUAL("scripts/awkscripts", ShortestEquivalentPath("scripts//./../scripts/awkscripts/././"));
    CHECK_EQUAL("/home", ShortestEquivalentPath("/home/"));
    // CHECK_EQUAL("/", ShortestEquivalentPath("/../"));
    CHECK_EQUAL("/home/foo", ShortestEquivalentPath("/home//foo/"));
    CHECK_EQUAL("/c", ShortestEquivalentPath("/a/./b/../../c/"));
}