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

int length(std::shared_ptr<ListNodeEPI<int>> l);

std::shared_ptr<ListNodeEPI<int>> createList(const std::vector<int>& vec);

std::shared_ptr<ListNodeEPI<int>> SearchList(std::shared_ptr<ListNodeEPI<int>> L, int key);

void InsertAfter(const std::shared_ptr<ListNodeEPI<int>>& node, const std::shared_ptr<ListNodeEPI<int>>& new_node);

void DeleteAfter(const std::shared_ptr<ListNodeEPI<int>>& node);

std::shared_ptr<ListNodeEPI<int>> MergeTwoSortedLists(std::shared_ptr<ListNodeEPI<int>> L1, std::shared_ptr<ListNodeEPI<int>> l2);

std::shared_ptr<ListNodeEPI<int>> ReverseSublist(std::shared_ptr<ListNodeEPI<int>> L, int start, int finish);

std::shared_ptr<ListNodeEPI<int>> HasCycle(const std::shared_ptr<ListNodeEPI<int>>& head);

std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1);

std::shared_ptr<ListNodeEPI<int>> OverlappingCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1);

void DeletionFromList(const std::shared_ptr<ListNodeEPI<int>>& node_to_delete);

std::shared_ptr<ListNodeEPI<int>> RemoveKthLast(const std::shared_ptr<ListNodeEPI<int>>& L, int k);

std::shared_ptr<ListNodeEPI<int>> RemoveDuplicates(const std::shared_ptr<ListNodeEPI<int>>& L);

std::shared_ptr<ListNodeEPI<int>> CyclicallyRightShiftList(std::shared_ptr<ListNodeEPI<int>> L, int k);

std::shared_ptr<ListNodeEPI<int>> EvenOddMerge(const std::shared_ptr<ListNodeEPI<int>>& L);

bool IsLinkedListPalindromic(const std::shared_ptr<ListNodeEPI<int>>& L);

std::shared_ptr<ListNodeEPI<int>> ListPivoting(const std::shared_ptr<ListNodeEPI<int>>& l, int x);

std::shared_ptr<ListNodeEPI<int>> AddTwoNumbers(std::shared_ptr<ListNodeEPI<int>> L1,
    std::shared_ptr<ListNodeEPI<int>> L2);

#endif // LINKEDLISTS_HPP