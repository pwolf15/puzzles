#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

std::vector<int> getValues(ListNode* node)
{
    std::vector<int> values;

    while (true)
    {
        if (node == nullptr)
        {
            break;
        }

        values.push_back(node->val);
        node = node->next;
    }

    return values;
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
    ListNode *deleteDuplicates(ListNode *head)
    {
        auto cur = head;
        auto prev = cur;
        if (cur == nullptr)
        {
            return head;
        }
        else
        {
            cur = cur->next;
        }
        
        while (true)
        {
            if (cur == nullptr)
            {
                break;
            }
            else
            {
                if (cur->val == prev->val)
                {
                    auto temp = cur;

                    if (cur->next != nullptr)
                    {
                        // connect nodes if not at end
                        prev->next = cur->next;                   
                    }
                    else
                    {
                        // set tail next ptr to null
                        prev->next = nullptr;
                    }

                    cur = prev->next;

                    // remove old node
                    delete temp;
                }
                else 
                {
                    prev = cur;
                    cur = cur->next;
                }
            }
        }

        return head;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        { },
        { 1, 1, 2 },
        { 1, 1, 2, 3, 3},
        { 1 }
    };

    const std::vector<std::vector<int>> expected = {
        { },
        { 1, 2 },
        { 1, 2, 3},
        { 1 }
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.deleteDuplicates(createList(test));
        printList(soln);
        assert(getValues(soln) == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}