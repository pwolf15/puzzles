#include <vector>
#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


void printList(ListNode* node) 
{
    int i = 0;
    while (true)
    {
        if (node == nullptr)
        {
            break;
        }
        else 
        {
            std::cout << "List[" << i++ << "]: " << node->val << std::endl;
            node = node->next;
        }
    }
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {

        // seed first node
        ListNode *merged = nullptr;
        ListNode *alt = nullptr;
        if (l1 == nullptr && l2 == nullptr)
        {
            merged = nullptr;
            return merged;
        }
        else if (l1 == nullptr)
        {
            merged = l2;
            return merged;
        }
        else if (l2 == nullptr)
        {
            merged = l1;
            return merged;
        }
        else if (l1->val <= l2->val)
        {
            merged = l1;
            alt = l2;
        }
        else
        {
            merged = l2;
            alt = l1;
        }

        ListNode *mergedFirst = merged;
        while (true)
        {
            if (alt == nullptr)
            {
                break;
            }
            else if (merged->next == nullptr)
            {
                merged->next = alt;
                break;
            }
            else if (merged->next->val <= alt->val)
            {
                merged = merged->next;
                std::cout << "HERE!" << std::endl;
                //break;
            }
            else
            {
                auto temp = merged->next;
                merged->next = alt;
                alt = temp;
                merged = merged->next;
                printList(mergedFirst);
                std::cout << "HERE1!" << std::endl;
            }
        }

        return mergedFirst;
    }
};

ListNode* createList(std::vector<int> vals)
{
    if (vals.size() == 0) 
    {
        return nullptr;
    }

    ListNode* node = new ListNode(vals[0]);
    ListNode* nodeFirst = node;
    for (auto i = 1; i < vals.size(); i++)
    {
        node->next = new ListNode(vals[i]);
        node = node->next;
    }

    return nodeFirst;
}

int main()
{
    Solution sol;

    // Input: 1->2->4, 1->3->4
    // Output: 1->1->2->3->4->4
    auto l1 = createList({1, 2, 4});
    auto l2 = createList({1, 3, 4});
    printList(l1);
    printList(l2);
    std::cout << std::endl << std::endl;
    auto l3 = sol.mergeTwoLists(l1, l2);
    printList(l3);
}