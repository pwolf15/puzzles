#include  "LinkedLists.hpp"
#include <string>
#include <vector>

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