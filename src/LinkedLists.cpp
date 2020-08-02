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