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

TEST(LinkedLists, MergeLists)
{
    std::shared_ptr<ListNodeEPI<int>> L1 = std::make_shared<ListNodeEPI<int>>();
    L1->data = 2;
    L1->next = std::make_shared<ListNodeEPI<int>>();
    L1->next->data = 5;
    L1->next->next = std::make_shared<ListNodeEPI<int>>();
    L1->next->next->data = 7;

    std::shared_ptr<ListNodeEPI<int>> L2 = std::make_shared<ListNodeEPI<int>>();
    L2->data = 3;
    L2->next = std::make_shared<ListNodeEPI<int>>();
    L2->next->data = 11;

    std::vector<int> values = { 2, 3, 5, 7, 11 };
    std::shared_ptr<ListNodeEPI<int>> cur = MergeTwoSortedLists(L1, L2);

    int i = 0;
    CHECK(cur != nullptr);
    while (cur)
    {
        CHECK_EQUAL(values[i], cur->data);
        cur = cur->next;
        i++;
    }

    CHECK_EQUAL(values.size(), i);

    L1 = createList({ 2, 5, 7});
    L2 = createList({ 3, 11 });
    cur = MergeTwoSortedLists(L1, L2);

    i = 0;
    CHECK(cur != nullptr);
    while (cur)
    {
        CHECK_EQUAL(values[i], cur->data);
        cur = cur->next;
        i++;
    }
};

TEST(LinkedLists, ReverseSublist)
{
    std::shared_ptr<ListNodeEPI<int>> L = createList({ 11, 7, 5, 3, 2});
    std::vector<int> values = { 11, 3, 5, 7, 2 };

    int i = 0;
    auto cur = ReverseSublist(L, 2, 4);
    CHECK(cur != nullptr);
    while (cur)
    {
        CHECK_EQUAL(values[i], cur->data);
        cur = cur->next;
        i++;
    }

    i = 0;
    L = createList({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    values = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    cur = ReverseSublist(L, 1, 10);
    CHECK(cur != nullptr);
    while (cur)
    {
        CHECK_EQUAL(values[i], cur->data);
        cur = cur->next;
        i++;
    }
};

TEST(LinkedLists, HasCycle)
{
    std::shared_ptr<ListNodeEPI<int>> L = std::make_shared<ListNodeEPI<int>>();
    L->data = 3;
    L->next = std::make_shared<ListNodeEPI<int>>();
    L->next->data = 2;
    L->next->next = std::make_shared<ListNodeEPI<int>>();
    L->next->next->data = 0;
    L->next->next->next = std::make_shared<ListNodeEPI<int>>();
    L->next->next->next->data = -4;
    L->next->next->next->next = L->next;

    auto cycleStart = HasCycle(L);
    CHECK(cycleStart == L->next);

    // cleanup memory
    L->next->next->next->next = nullptr;

    L->next = nullptr;

    cycleStart = HasCycle(L);
    CHECK(cycleStart == nullptr);
};