#ifndef LINKEDLISTS_HPP
#define LINKEDLISTS_HPP

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *reverseList(ListNode *head);

bool isPalindrome(ListNode* head);

#endif // LINKEDLISTS_HPP