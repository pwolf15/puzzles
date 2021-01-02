#include  "LinkedLists.hpp"
#include <string>
#include <vector>
#include <iostream>

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr)
    {
        return head;
    }

    ListNode* reversed  = head;
    ListNode* forward   = head->next;
    reversed->next = nullptr;

    while (true)
    {
        if (!forward || !reversed)
        {
            break;
        }

        auto temp = forward->next;
        forward->next = reversed;
        reversed = forward;
        forward = temp;
    }

    return reversed;
}

bool isPalindrome(ListNode* head)
{
    auto cur = head;
    std::vector<int> vec;
    while (cur)
    {
        vec.push_back(cur->val);
        cur = cur->next;
    }

    bool isPal = true;
    for (size_t i = 0; i < vec.size() / 2; ++i)
    {
        if (vec[i] != vec[vec.size() - 1 - i])
        {
            isPal = false;
        }
    }

    return isPal;
}

std::shared_ptr<ListNodeEPI<int>> createList(const std::vector<int>& vec)
{
    std::shared_ptr<ListNodeEPI<int>> head = nullptr;
    std::shared_ptr<ListNodeEPI<int>> cur = head;

    if (vec.empty()) return head;

    head = std::make_shared<ListNodeEPI<int>>();
    head->data = vec[0];
    cur = head;

    for (int i = 1; i < vec.size(); ++i)
    {
        cur->next = std::make_shared<ListNodeEPI<int>>();
        cur->next->data = vec[i];
        cur = cur->next; 
    }

    return head;
}

std::shared_ptr<ListNodeEPI<int>> SearchList_PW(std::shared_ptr<ListNodeEPI<int>> L, int key)
{
    std::shared_ptr<ListNodeEPI<int>> cur = L;
    while (cur != nullptr)
    {
        if (cur->data == key)
        {
            break;
        }
        else
        {
            cur = cur->next;
        }
    }

    return cur;
}

std::shared_ptr<ListNodeEPI<int>> SearchList_EPI(std::shared_ptr<ListNodeEPI<int>> L, int key) {
    while (L && L->data != key) {
        L = L->next;
    }
    // If key was not present in the list, L will have become null.
    return L;
}

std::shared_ptr<ListNodeEPI<int>> SearchList(std::shared_ptr<ListNodeEPI<int>> L, int key)
{
    return SearchList_EPI(L, key);
}

void InsertAfter_PW(const std::shared_ptr<ListNodeEPI<int>>& node, const std::shared_ptr<ListNodeEPI<int>>& new_node)
{
    if (node->next == nullptr)
    {
        node->next = new_node;
        return;
    }

    std::shared_ptr<ListNodeEPI<int>> temp = node->next;
    node->next = new_node;
    new_node->next = temp;
}

// Inserts new_node after node.
void InsertAfter_EPI(const std::shared_ptr<ListNodeEPI<int>>& node, const std::shared_ptr<ListNodeEPI<int>>& new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

void InsertAfter(const std::shared_ptr<ListNodeEPI<int>>& node, const std::shared_ptr<ListNodeEPI<int>>& new_node)
{
    return InsertAfter_EPI(node, new_node);
}


void DeleteAfter_PW(const std::shared_ptr<ListNodeEPI<int>>& node)
{
    if (node->next)
    {
        node->next = node->next->next;
    } 
    else
    {
        node->next = nullptr;
    }
}

// Delete the node past this one. Assume node is not a tail.
void DeleteAfter_EPI(const std::shared_ptr<ListNodeEPI<int>>& node)
{
    node->next = node->next->next;
}

void DeleteAfter(const std::shared_ptr<ListNodeEPI<int>>& node)
{
    return DeleteAfter_EPI(node);
}

// space complexity: O(1)
// time complexity: O(n + m), where n and m length of L1 and L2
std::shared_ptr<ListNodeEPI<int>> MergeTwoSortedLists_PW(std::shared_ptr<ListNodeEPI<int>> L1, std::shared_ptr<ListNodeEPI<int>> L2)
{
    if (!L1) return L2;
    if (!L2) return L1;

    auto left = L1->data <= L2->data ? L1 : L2;
    auto right = L1 == left ? L2 : L1;
    std::shared_ptr<ListNodeEPI<int>> merged = left;
    auto prev = left;

    while (true)
    {
        // advance left ptr until left's data less than right      
        while (left && left->data <= right->data)
        {
            prev = left;
            left = left->next;
        }

        // if left exhausted during search, break
        if (!left)
        {
            break;
        }

        // else, right data less than left, swap ptrs, advance dummy ptr
        auto temp = right;
        right = left;
        left = temp;

        prev->next = left;
    }

    // only way to reach here is that left has been exhausted
    prev->next = right;

    return merged;
}

void AppendNode(std::shared_ptr<ListNodeEPI<int>> *node, std::shared_ptr<ListNodeEPI<int>> *tail)
{
    (*tail)->next = *node;
    *tail = *node;
    *node = (*node)->next;
}

// space complexity: O(1)
// time complexity: O(n + m), where n and m length of L1 and L2
std::shared_ptr<ListNodeEPI<int>> MergeTwoSortedLists_EPI(std::shared_ptr<ListNodeEPI<int>> L1, std::shared_ptr<ListNodeEPI<int>> L2)
{
    // Creates a placeholder for the result.
    std::shared_ptr<ListNodeEPI<int>> dummy_head(new ListNodeEPI<int>);
    auto tail = dummy_head;

    while (L1 && L2) {
        AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
    }

    // Appends the remaining nodes of L1 or L2.
    tail->next = L1 ? L1 : L2;
    return dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> MergeTwoSortedLists(std::shared_ptr<ListNodeEPI<int>> L1, std::shared_ptr<ListNodeEPI<int>> L2)
{
    return MergeTwoSortedLists_EPI(L1, L2);
}

std::shared_ptr<ListNodeEPI<int>> ReverseSublist_PW(std::shared_ptr<ListNodeEPI<int>> L, int start, int finish)
{
    auto dummy_head = std::make_shared<ListNodeEPI<int>>();
    dummy_head->next = L;

    // tail points at last element in sub-list
    auto tail = dummy_head;
    auto prev = tail;

    // move prev to point at element before start node
    int i = 0;
    while (i < start)
    {
        i++;
        prev = tail;
        tail = tail->next;
    }

    // continuouslly shift first in sub-list with current tail
    while (i < finish)
    {
        i++;
        auto prevHead = prev->next;
        prev->next = tail->next;
        auto prevDummyTail = tail->next->next;
        prev->next->next = prevHead;

        tail->next = prevDummyTail;
    }

    return dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> ReverseSublist(std::shared_ptr<ListNodeEPI<int>> L, int start, int finish)
{
    return ReverseSublist_PW(L, start, finish);
}