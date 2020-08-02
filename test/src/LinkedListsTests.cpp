#include <iostream>
#include <vector>

#include "CppUTest/TestHarness.h"

#include "LinkedLists.hpp"

TEST_GROUP(LinkedLists)
{
 
};

TEST(LinkedLists, Reverse)
{
    // new linked lists
    ListNode* head = new ListNode(0);
    ListNode* cur = head;
    for (size_t i = 1; i < 5; i++)
    {
        cur->next = new ListNode(i);
        cur = cur->next;
    }

    cur = head;
    size_t i = 0;
    while (cur)
    {
        cur = cur->next;
        i++;
    }

    auto temp = head;
    cur = reverseList(temp);
    head = cur;
    i = 0;
    while (cur)
    {
        cur = cur->next;
        i++;
    }

    reverseList(nullptr);
    auto single = new ListNode(0);
    auto reversedSingle = reverseList(single);
    delete reversedSingle;

    i = 0;
    cur = head;
    while (cur)
    {
        auto temp = cur->next;
        delete cur;
        cur = temp;
        i++;
    }
};

TEST(LinkedLists, isPalindrome)
{
    // new linked lists
    ListNode* head = new ListNode(0);
    ListNode* cur = head;
    for (size_t i = 1; i < 5; i++)
    {
        cur->next = new ListNode(i);
        cur = cur->next;
    }

    cur = head;
    
    CHECK(!isPalindrome(cur));

    size_t i = 0;
    cur = head;
    while (cur)
    {
        auto temp = cur->next;
        delete cur;
        cur = temp;
        i++;
    }

    head = new ListNode(1);
    cur = head;

    std::vector<int> vec = { 2, 2, 1 };
    for (i = 0; i < vec.size(); i++)
    {
        cur->next = new ListNode(vec[i]);
        cur = cur->next;
    }

    cur = head;
    
    CHECK(isPalindrome(cur));

    i = 0;
    cur = head;
    while (cur)
    {
        auto temp = cur->next;
        delete cur;
        cur = temp;
        i++;
    }
};
