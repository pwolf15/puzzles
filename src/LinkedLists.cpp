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

// time complexity: O(m * l), where m is length of l0 and l is length of l1
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists_PW2(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    for (auto i = l0; i != nullptr; i = i->next)
    {
        for (auto j = l1; j != nullptr; j = j->next)
        {
            if (i == j)
            {
                return i;
            }
        }
    }

    return nullptr;
}

// time complexity: O(m + l), where m is length of l0 and l is length of l1
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists_PW3(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    // get sizes of each list
    int len0 = 0;
    for (auto i = l0; i != nullptr; i = i->next)
    {
        len0++;
    }

    int len1 = 0;
    for (auto i = l1; i != nullptr; i = i->next)
    {
        len1++;
    }

    // if one list larger than the other
    //  advance it until lists the same size
    // reasoning: if lists same size, we can just advance each one node
    // at a time simultaneously. There must be an intersection at some common node.
    if (len0 > len1)
    {
        for (int i = 0; i < len0 - len1; ++i)
        {
            l0 = l0->next;
        }

        len0 = len1;
    }
    else if (len1 > len0)
    {
        for (int i = 0; i < len1 - len0; ++i)
        {
            l1 = l1->next;
        }

        len1 = len0;
    }

    for (int i = 0; i < len0; ++i)
    {
        if (l0 == l1)
        {
            return l0;
        }

        l0 = l0->next;
        l1 = l1->next;
    }

    return nullptr;
}

int Length(std::shared_ptr<ListNodeEPI<int>> L) {
    int length = 0;
    while (L) {
        ++length, L = L->next;
    }
    return length;
}

// Advances L by k steps.
void AdvanceListByK(int k, std::shared_ptr<ListNodeEPI<int>>* L) {
    while (k--) {
        *L = (*L)->next;
    }
}

// time complexity: O(m + l), where m is length of l0 and l is length of l1
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists_EPI(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    int l0_len = Length(l0), l1_len = Length(l1);

    // Advances the longer list to get equal length lists.
    AdvanceListByK(std::abs(l0_len - l1_len), l0_len > l1_len ? &l0 : &l1);

    while (l0 && l1 && l0 != l1) {
        l0 = l0->next, l1 = l1->next;
    }
    return l0; // nullptr implies there is no overlap between l0 and l1
}

std::shared_ptr<ListNodeEPI<int>> OverlappingNoCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    return OverlappingNoCycleLists_EPI(l0, l1);
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

// time complexity: O(m + l), where m is length of l0 and l is length of l1
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> OverlappingCycleLists_EPI(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    // case analysis
    // 1. both neither have cycles => use OverlappingNoCycleLists solution.
    // 2. one has a cycle, the other does not => they can't overlap.
    // 3. both have cycles => cycle must be identical
    //  traverse cycle of first list
    //  if we reach head of first list, there is no overlap
    //  otherwise return 

    // Store the start of cycle if any.
    auto root0 = HasCycle(l0), root1 = HasCycle(l1);

    if (!root0 && !root1) {
        // Both lists don't have cycles
        return OverlappingNoCycleLists(l0, l1);
    } else if ((root0 && !root1) || (!root0 && root1)) {
        // One list has cycle, and one list has no cycle.
        return nullptr;
    }

    // Both lists have cycles.
    auto temp = root1;
    do {
        temp = temp->next;
    } while (temp != root0 && temp != root1);

    return temp == root0 ? root1 : nullptr;
}

std::shared_ptr<ListNodeEPI<int>> OverlappingCycleLists(std::shared_ptr<ListNodeEPI<int>> l0, 
    std::shared_ptr<ListNodeEPI<int>> l1)
{
    return OverlappingCycleLists_EPI(l0, l1);
}

// Assumes node_to_delete is not tail.
// time complexity: O(1)
// space complexity: O(1)
void DeletionFromList(const std::shared_ptr<ListNodeEPI<int>>& node_to_delete)
{
    node_to_delete->data = node_to_delete->next->data;
    node_to_delete->next = node_to_delete->next->next;
}

// space complexity: O(1)
// time complexity: O(N)
std::shared_ptr<ListNodeEPI<int>> RemoveKthLast_PW(const std::shared_ptr<ListNodeEPI<int>>& L, int k)
{
    auto h1 = L;
    auto h2 = h1;
    auto head = L;

    // advance h1 k nodes
    //  to find kth from last node
    for (int i = 0; i < k; ++i)
    {
        h1 = h1->next;
    }

    // if h1 is nullptr, that means that
    //  node to remove is the 1st node
    if (h1 == nullptr)
    {
        head = h2->next;
        return head;
    }

    // otherwise, advance h1 1 node
    //  we want h2->next to point to node to remove
    h1 = h1->next;

    // advance both pointers to the end
    while (h1 != nullptr)
    {
        h1 = h1->next;
        h2 = h2->next;
    }

    // remove the node of interest
    h2->next = h2->next->next;

    return head;
}

std::shared_ptr<ListNodeEPI<int>> RemoveKthLast_EPI(const std::shared_ptr<ListNodeEPI<int>>& L, int k)
{
    auto dummy_head = std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{0, L});
    auto first = dummy_head->next;
    while (k--) {
        first = first->next;
    }

    auto second = dummy_head;
    while (first) {
        second = second->next, first = first->next;
    }
    // second points to the (k+1)-th last node, deletes its successor
    second->next = second->next->next;
    return dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> RemoveKthLast(const std::shared_ptr<ListNodeEPI<int>>& L, int k)
{
    return RemoveKthLast_EPI(L, k);
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> RemoveDuplicates_PW(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    auto first = L;
    auto second = first;

    while (second != nullptr)
    {
        if (second->data != first->data)
        {
            first->next = second;
            first = second;
        }

        second = second->next;
    }

    if (first && first->next != nullptr)
    {
        first->next = nullptr;
    }

    return L;
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> RemoveDuplicates_EPI(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    auto iter = L;
    while (iter) {
        // Uses next_distinct to find the next distinct value.
        auto next_distinct = iter->next;
        while (next_distinct && next_distinct->data == iter->data) {
            next_distinct = next_distinct->next;
        }
        iter->next = next_distinct;
        iter = next_distinct;
    }
    return L;
}

std::shared_ptr<ListNodeEPI<int>> RemoveDuplicates(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    return RemoveDuplicates_EPI(L);
}

int length(std::shared_ptr<ListNodeEPI<int>> l)
{
    int length = 0;
    while (l != nullptr)
    {
        l = l->next;
        length++;
    }
    return length;
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> CyclicallyRightShiftList_PW(std::shared_ptr<ListNodeEPI<int>> L, int k)
{
    auto p1 = L;
    int count = 0;
    auto newTail = p1;

    if (L == nullptr) return L;
    
    auto len = length(L);
    k = k % len; 

    if (k == 0) return L;

    while (count < (len - k))
    {
        p1 = p1->next;
        if (count >= 1)
        {
            newTail = newTail->next;
        }
        
        count++;
    }

    auto p2 = p1;
    auto newHead = p1;
    std::cout << "val: " << p1->data << std::endl;
    while (p2->next != nullptr)
    {
        p2 = p2->next;
    }
    p2->next = L;
    newTail->next = nullptr;
    return newHead;
}

std::shared_ptr<ListNodeEPI<int>> CyclicallyRightShiftList_EPI(std::shared_ptr<ListNodeEPI<int>> L, int k)
{
    if (L == nullptr) {
        return L;
    }

    // Computes the length of L and the tail.
    auto tail = L;
    int n = 1;
    while (tail->next) {
        ++n, tail = tail->next;
    }
    k %= n;
    if (k == 0) {
        return L;
    }

    tail->next = L; // Makes a cycle by connecting the tail to the head.
    int steps_to_new_head = n - k;
    auto new_tail = tail;

    // goes to tail
    //  determines steps to new head from current head
    //  identifies new_tail, assigns new head as new_tail->next
    //  nulls next ptr of new_tail
    // original head becomes kth node
    // (n-kth) node becomes head
    while (steps_to_new_head--) {
        new_tail = new_tail->next;
    }
    auto new_head = new_tail->next;
    new_tail->next = nullptr;
    return new_head;
}

std::shared_ptr<ListNodeEPI<int>> CyclicallyRightShiftList(std::shared_ptr<ListNodeEPI<int>> L, int k)
{
    return CyclicallyRightShiftList_EPI(L, k);
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> EvenOddMerge_PW(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    if (L == nullptr) {
        return L;
    }

    auto p1 = L;        // tail of evens
    auto p2 = L->next;  // start of "rest"
    auto startOdd = p2;

    while (p2 && p2->next)
    {
        // move successor node of "rest" to tail of evens
        p1->next = p2->next;
        p2->next = p1->next->next;

        // advance tail of evens
        // advance head of "rest"
        p1 = p1->next;
        p2 = p2->next;
    }

    // append both lists
    p1->next = startOdd;

    return L;
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> EvenOddMerge_EPI(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    if (L == nullptr) {
        return L;
    }

    auto even_dummy_head = std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{0, nullptr});
    auto odd_dummy_head = std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{0, nullptr});
    std::array<std::shared_ptr<ListNodeEPI<int>>, 2> tails = {even_dummy_head, odd_dummy_head};

    int turn = 0;
    for (auto iter = L; iter; iter = iter->next) {
        tails[turn]->next = iter;
        tails[turn] = tails[turn]->next;
        turn ^= 1; // Alternate between even and odd
    }

    tails[1]->next = nullptr;
    tails[0]->next = odd_dummy_head->next;

    return even_dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> EvenOddMerge(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    return EvenOddMerge_EPI(L);
}

// time O(4*n): 1. get to end, 2. copy list, 3. traverse half new list 4. traverse second half new list
// space O(n): need to create copy of list
bool IsLinkedListPalindromic_PW(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    // advance to end
    auto p1 = L;
    auto p2 = L;

    while (p1 && p1->next)
    {
        p1 = p1->next;
    }

    auto end = p1;

    while (p2 != end)
    {
        auto temp = p1->next;
        p1->next = std::make_shared<ListNodeEPI<int>>();
        p1->next->data = p2->data;
        p1->next->next = temp;
        p2 = p2->next;
    }

    auto p6 = L;

    while (p6)
    {
        p6 = p6->next;
    }

    // traverse
    auto p4 = L;
    auto p5 = end;
    while (p4 != end && p5 != nullptr)
    {
        if (p4->data != p5->data)
        {
            return false;
        }

        p4 = p4->next;
        p5 = p5->next;
    }

    return true;
}

std::shared_ptr<ListNodeEPI<int>> ReverseList(std::shared_ptr<ListNodeEPI<int>>& L)
{
    auto head = L;

    auto tail = head;
    while (tail && tail->next)
    {
        tail = tail->next;
    }

    auto newHead = tail;
    while (head != newHead)
    {
        auto temp = tail->next;
        tail->next = head;
        head = head->next;
        tail->next->next = temp;
    }
    return newHead;
}

// time O(n)
// space O(1)
bool IsLinkedListPalindromic_EPI(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    // Finds the second half of L.
    std::shared_ptr<ListNodeEPI<int>> slow = L, fast = L;
    while (fast && fast->next)
    {
        fast = fast->next->next, slow = slow->next;
    }

    // Compares the first half and the reversed second half lists.
    auto first_half_iter = L, second_half_iter = ReverseList(slow);
    while (second_half_iter && first_half_iter) {
        if (second_half_iter->data != first_half_iter->data) {
            return false;
        }
        second_half_iter = second_half_iter->next;
        first_half_iter = first_half_iter->next;
    }
    return true;
}

bool IsLinkedListPalindromic(const std::shared_ptr<ListNodeEPI<int>>& L)
{
    return IsLinkedListPalindromic_EPI(L);
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> ListPivoting_PW(const std::shared_ptr<ListNodeEPI<int>>& l, int x)
{
    std::shared_ptr<ListNodeEPI<int>> greater_than(new ListNodeEPI<int>);
    std::shared_ptr<ListNodeEPI<int>> less_than(new ListNodeEPI<int>); 
    std::shared_ptr<ListNodeEPI<int>> equal_to(new ListNodeEPI<int>); 

    auto gt = greater_than;
    auto lt = less_than;
    auto et = equal_to;

    auto p = l;
    while (p) 
    {
        if (p->data > x)
        {
            greater_than->next = p;
            greater_than = greater_than->next;
        }
        else if (p->data == x)
        {
            equal_to->next = p;
            equal_to = equal_to->next;
        }
        else if (p->data < x)
        {
            less_than->next = p;
            less_than = less_than->next;
        }
        p = p->next;
    }

    auto newHead = lt->next;
    less_than->next = et->next;
    equal_to->next = gt->next;

    return newHead;
}

// time complexity: O(n)
// space complexity: O(1)
std::shared_ptr<ListNodeEPI<int>> ListPivoting_EPI(const std::shared_ptr<ListNodeEPI<int>>& l, int x)
{
    std::shared_ptr<ListNodeEPI<int>> less_head(new ListNodeEPI<int>),
        equal_head(new ListNodeEPI<int>), greater_head(new ListNodeEPI<int>); 
    std::shared_ptr<ListNodeEPI<int>> less_iter = less_head, equal_iter = equal_head,
                                      greater_iter = greater_head;
    // Populates the three lists.
    std::shared_ptr<ListNodeEPI<int>> iter = l;
    while (iter) {
        AppendNode(&iter, iter->data < x 
                            ? &less_iter 
                            : iter->data == x ? &equal_iter : &greater_iter);
    }
    // Combines the three lists.
    greater_iter->next = nullptr;
    equal_iter->next = greater_head->next;
    less_iter->next = equal_head->next;
    return less_head->next;
}

std::shared_ptr<ListNodeEPI<int>> ListPivoting(const std::shared_ptr<ListNodeEPI<int>>& l, int x)
{
    return ListPivoting_EPI(l, x);
}

// time complexity: O(n)
// space complexity: O(n)
std::shared_ptr<ListNodeEPI<int>> AddTwoNumbers_PW(std::shared_ptr<ListNodeEPI<int>> L1,
    std::shared_ptr<ListNodeEPI<int>> L2)
{
    std::shared_ptr<ListNodeEPI<int>> L3 = std::make_shared<ListNodeEPI<int>>();
    auto head = L3;
    int carry = 0;
    int sum = 0;
    while (L1 && L2)
    {
        sum = L1->data + L2->data + carry;
        carry = sum / 10;
        sum %= 10;
        L3->next = std::make_shared<ListNodeEPI<int>>();
        L3->next->data = sum;
        L1 = L1->next;
        L2 = L2->next;
        L3 = L3->next;
    }

    if (L1)
    {
        while (L1)
        {
            sum = L1->data + carry;
            carry = sum / 10;
            sum %= 10;
            L3->next = std::make_shared<ListNodeEPI<int>>();
            L3->next->data = sum;
            L1 = L1->next;
            L3 = L3->next;
        }
    }
    else if (L2)
    {
        while (L2)
        {
            sum = L2->data + carry;
            carry = sum / 10;
            sum %= 10;
            L3->next = std::make_shared<ListNodeEPI<int>>();
            L3->next->data = sum;
            L2 = L2->next;
            L3 = L3->next;
        }
    }
    
    if (carry)
    {
        L3->next = std::make_shared<ListNodeEPI<int>>();
        L3->next->data = carry;
    }

    return head->next;
}

// time complexity: O(n+m)
// space complexity: O(max(n, m))
std::shared_ptr<ListNodeEPI<int>> AddTwoNumbers_EPI(std::shared_ptr<ListNodeEPI<int>> L1,
    std::shared_ptr<ListNodeEPI<int>> L2)
{
    std::shared_ptr<ListNodeEPI<int>> dummy_head(new ListNodeEPI<int>);
    auto place_iter = dummy_head;
    int carry = 0;
    while (L1 || L2 || carry) {
        int val = carry + (L1 ? L1->data : 0) + (L2 ? L2->data : 0);
        L1 = L1 ? L1->next : nullptr;
        L2 = L2 ? L2->next : nullptr;
        place_iter->next =
            std::make_shared<ListNodeEPI<int>>(ListNodeEPI<int>{val % 10, nullptr});
        carry = val / 10, place_iter = place_iter->next;
    }
    return dummy_head->next;
}

std::shared_ptr<ListNodeEPI<int>> AddTwoNumbers(std::shared_ptr<ListNodeEPI<int>> L1,
    std::shared_ptr<ListNodeEPI<int>> L2)
{
    return AddTwoNumbers_EPI(L1, L2);
}

// time complexity: O(n)
// space complexity: O(1)
int getDecimalValue(std::shared_ptr<ListNodeEPI<int>> head)
{
    int value = 0;
    while (head)
    {
        value <<= 1;
        value += head->data;
        head = head->next;
    }
    return value;
}