#ifndef LINKEDLISTS_HPP
#define LINKEDLISTS_HPP

#include <memory>
#include <vector>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template <typename T>
struct ListNodeEPI
{
    T data;
    std::shared_ptr<ListNodeEPI<T>> next;
};

ListNode *reverseList(ListNode *head);

bool isPalindrome(ListNode* head);

std::shared_ptr<ListNodeEPI<int>> createList(const std::vector<int>& vec);

std::shared_ptr<ListNodeEPI<int>> SearchList(std::shared_ptr<ListNodeEPI<int>> L, int key);

void InsertAfter(const std::shared_ptr<ListNodeEPI<int>>& node, const std::shared_ptr<ListNodeEPI<int>>& new_node);

void DeleteAfter(const std::shared_ptr<ListNodeEPI<int>>& node);

std::shared_ptr<ListNodeEPI<int>> MergeTwoSortedLists(std::shared_ptr<ListNodeEPI<int>> L1, std::shared_ptr<ListNodeEPI<int>> l2);

#endif // LINKEDLISTS_HPP