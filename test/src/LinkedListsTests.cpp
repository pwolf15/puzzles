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


TEST(LinkedLists, SearchList)
{
    std::shared_ptr<ListNodeEPI<int>> head = std::make_shared<ListNodeEPI<int>>();
    head->data = 1;
    head->next = std::make_shared<ListNodeEPI<int>>();
    head->next->data = 2;
    head->next->next = std::make_shared<ListNodeEPI<int>>();
    head->next->next->data = 3;

    std::shared_ptr<ListNodeEPI<int>> result = SearchList(head, 2);
    CHECK(result != nullptr);
    CHECK_EQUAL(2, result->data);
};


TEST(LinkedLists, InsertAfter)
{
    std::shared_ptr<ListNodeEPI<int>> head = std::make_shared<ListNodeEPI<int>>();
    head->data = 1;
    head->next = std::make_shared<ListNodeEPI<int>>();
    head->next->data = 2;
    head->next->next = std::make_shared<ListNodeEPI<int>>();
    head->next->next->data = 3;

    std::shared_ptr<ListNodeEPI<int>> newNode1 = std::make_shared<ListNodeEPI<int>>();
    newNode1->data = 4;

    InsertAfter(head->next, newNode1);
    CHECK_EQUAL(4, head->next->next->data);

    std::shared_ptr<ListNodeEPI<int>> newNode2 = std::make_shared<ListNodeEPI<int>>();
    newNode2->data = 5;
    
    InsertAfter(head->next->next->next, newNode2);
    CHECK_EQUAL(5, head->next->next->next->next->data);
};

TEST(LinkedLists, DeleteAfter)
{
    std::shared_ptr<ListNodeEPI<int>> head = std::make_shared<ListNodeEPI<int>>();
    head->data = 1;
    head->next = std::make_shared<ListNodeEPI<int>>();
    head->next->data = 2;
    head->next->next = std::make_shared<ListNodeEPI<int>>();
    head->next->next->data = 3;

    DeleteAfter(head);
    CHECK_EQUAL(3, head->next->data);

    DeleteAfter(head);
    CHECK(head->next == nullptr);
};