#include  "LinkedLists.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

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

// time complexity: O(n)
// space complexity: O(1)
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

// time complexity: O(n), where n is length of list O(f), where f is fth node
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> ReverseSublist_EPI(std::shared_ptr<ListNodeEPI<int>> L, int start, int finish)
{
    auto dummy_head = std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{0, L});
    auto sublist_head = dummy_head;
    int k = 1;
    while(k++ < start) {
        sublist_head = sublist_head->next;
    }

    // Reverses sublist.
    auto sublist_iter = sublist_head->next;
    while (start++ < finish) {
        auto temp = sublist_iter->next;
        sublist_iter->next = temp->next;
        temp->next = sublist_head->next;
        sublist_head->next = temp;
    }
    return dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> ReverseSublist(std::shared_ptr<ListNodeEPI<int>> L, int start, int finish)
{
    return ReverseSublist_EPI(L, start, finish);
}

bool CycleCheck(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    auto slow = head;
    auto fast = head;

    bool hasCycle = false;
    while (slow != nullptr && fast != nullptr)
    {
        fast = fast->next;
        slow = slow->next;

        if (!fast)
        {
            break;
        }
        
        if (!fast->next)
        {
            break;
        }
        else 
        {
            fast = fast->next;
        }

        if (fast == slow)
        {
            if (fast == head) 
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return hasCycle;
}

// time complexity: O(2N * N) = O(N^2), for each, we are doing the cycle check. Cycle check is 2N
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> HasCycle_PW(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    auto dummy_head = std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{0, head});
    while (dummy_head != nullptr && dummy_head->next != nullptr)
    {
        if (CycleCheck(dummy_head->next))
        {
            return dummy_head->next;
        }
       
        dummy_head = dummy_head->next;
    }

    return nullptr;
}

// time complexity: O(N)
// space complexity: O(N)
std::shared_ptr<ListNodeEPI<int>> HasCycle_BF(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    std::unordered_set<std::shared_ptr<ListNodeEPI<int>>> nodes;
    auto cur = head;

    while (cur != nullptr)
    {
        auto it = nodes.find(cur);
        if (it == nodes.end())
        {
            nodes.insert(cur);
        }
        else
        {
            return *it;
        }

        cur = cur->next;
    }

    return nullptr;
}

// time complexity: O(N^2)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> HasCycle_BF2(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    std::unordered_set<std::shared_ptr<ListNodeEPI<int>>> nodes;
    auto cur = head;

    int count = 0;

    // for each node, step through as many nodes seen thus far
    //  if we see the same node twice, you've hit the start
    //  return the start of the cycle
    for (auto i = head; i != nullptr; i = i->next)
    {
        count++;
        auto cur2 = head;
        int curCount = 0;
        for (auto j = 0; j < count; ++j)
        {
            if (cur2 == i)
            {
                curCount++;
                if (curCount == 2)
                {
                    return cur2;
                }
            }

            cur2 = cur2->next;
        }
    }

    return nullptr;
}

// time complexity: O(N)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> HasCycle_PW2(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    if (!head) { return head; }

    auto slow = head, fast = head->next;

    // fast iterator will catch up with slow iterator (Floyd's algorithm)
    // If there is a cycle, when both pointers are in cycle, the fast iterator
    // will increase its distance by 1 with each iteration. By at least the last step of slow iterator's first
    // step through cycle, it will have caught up with the slow iterator. (Think tortoise and hare).

    while (fast && fast->next)
    {
        if (slow == fast)
        {
            // get length of cycle
            int cycleLen = 1;
            fast = fast->next;
            while (fast != slow) 
            {
                fast = fast->next;
                cycleLen++;
            }

            // return to stsart
            slow = head;
            fast = head;

            // iterate fast ptr to cycle length
            while (cycleLen)
            {
                fast = fast->next;
                cycleLen--;
            }

            // because fast ptr is cycleLen nodes ahead,
            //    by the time you reach this condition, fast will have iterated a cycle
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
                            
            }

            return slow;
        }

        slow = slow->next;
        fast = fast->next->next;
    }

    return nullptr;
}

// F = number of nodes to ethe start of the cycle, C = number of nodes in cycle, n = number of nodes
// time complexity: O(F) + O(C) = O(n) => O(F) for both pointers to reach the cycle and O(C) for them to overlap once the slower one enters
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> HasCycle_EPI(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    if (!head) { return head; }

    std::shared_ptr<ListNodeEPI<int>> fast = head, slow = head;

    while (fast && fast->next)
    {
        slow = slow->next, fast = fast->next->next;
        if (slow == fast) {

            // There is a cycle, so let's calculate the cycle length.
            int cycle_len = 0;
            do {
                ++cycle_len;
                fast = fast->next;
            } while (slow != fast);

            // Finds the start of the cycle.
            auto cycle_len_advanced_iter = head;
            while (cycle_len--) {
                cycle_len_advanced_iter = cycle_len_advanced_iter->next;
            }

            auto iter = head;
            // Both iterats advance in tandem.
            while (iter != cycle_len_advanced_iter) {
                iter = iter->next;
                cycle_len_advanced_iter = cycle_len_advanced_iter->next;
            }
            return iter; // iter is the start of the cycle
        }
    }
    return nullptr; // No cycle.
}

std::shared_ptr<ListNodeEPI<int>> HasCycle(const std::shared_ptr<ListNodeEPI<int>>& head)
{
    return HasCycle_EPI(head);
}

// time complexity: O(m + l), where m is length of l0 and l is length of l1
// space complexity: O(m)
std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists_PW(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    std::unordered_set<std::shared_ptr<ListNodeEPI<int>>> nodes;
    std::shared_ptr<ListNodeEPI<int>> commonNode;

    auto cur = l0;
    while (cur != nullptr)
    {
        nodes.insert(cur);
        cur = cur->next;
    }

    cur = l1;
    while (cur != nullptr)
    {
        auto it = nodes.find(cur);
        if (it != nodes.end())
        {
            commonNode = *it;
            break;
        }
        cur = cur->next;
    }

    return commonNode;
}

std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    return OverlappingNoCycleLists_PW(l0, l1);
}


// time complexity: O(m + l), where m is length of l0 and l is length of l1
// space complexity: O(m)
std::shared_ptr<ListNodeEPI<int>> OverlappingCycleLists_PW(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    std::unordered_set<std::shared_ptr<ListNodeEPI<int>>> nodes;
    std::shared_ptr<ListNodeEPI<int>> commonNode;

    auto cur = l0;
    while (cur != nullptr)
    {
        if (nodes.find(cur) != nodes.end())
        {
            break;
        }

        nodes.insert(cur);
        cur = cur->next;
    }

    cur = l1;
    std::unordered_set<std::shared_ptr<ListNodeEPI<int>>> nodes_l1;
    while (cur != nullptr)
    {
        auto it = nodes.find(cur);
        if (it != nodes.end())
        {
            commonNode = *it;
            break;
        }

        nodes.insert(cur);

        it = nodes_l1.find(cur);
        if (it != nodes_l1.end())
        {
            // hit cycle
            return nullptr;
        }
        
        nodes_l1.insert(cur);
        cur = cur->next;
    }

    return commonNode;
}

std::shared_ptr<ListNodeEPI<int>> OverlappingCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    return OverlappingCycleLists_PW(l0, l1);
}

// Assumes node_to_delete is not tail.
// time complexity: O(1)
// space complexity: O(1)
void DeletionFromList(const std::shared_ptr<ListNodeEPI<int>>& node_to_delete)
{
    node_to_delete->data = node_to_delete->next->data;
    node_to_delete->next = node_to_delete->next->next;
}