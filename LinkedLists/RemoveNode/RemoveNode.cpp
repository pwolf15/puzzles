#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *createList(std::vector<int> vals)
{
    if (vals.size() == 0)
    {
        return nullptr;
    }

    ListNode *node = new ListNode(vals[0]);
    ListNode *nodeFirst = node;
    for (auto i = 1; i < vals.size(); i++)
    {
        node->next = new ListNode(vals[i]);
        node = node->next;
    }

    return nodeFirst;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        while (true)
        {
            if (node == nullptr)
            {
                return;
            }
            else
            {
                // since we don't have pointer to head,
                //  we need to just shift values and delete last ptr
                if (node->next && node->next->next == nullptr)
                {
                    node->val = node->next->val;
                    delete node->next;
                    node->next = nullptr;
                    return;
                }
                else
                {
                    node->val = node->next->val;
                    node = node->next;
                }
            }
        }
    }
};

bool equal(ListNode *a, ListNode *b)
{
    if (a == nullptr && b == nullptr)
    {
        return true;
    }
    else if (a == nullptr || b == nullptr)
    {
        return true;
    }
    else
    {
        return a->val != b->val ? false : equal(a->next, b->next);
    }
}

void printList(ListNode *a)
{
    while (true)
    {
        if (a == nullptr)
        {
            return;
        }
        else
        {
            std::cout << a->val << std::endl;
            a = a->next;
        }
    }
}

int main()
{

    Solution sol;

    auto list = createList({4, 5, 1, 9});
    const std::vector<ListNode *> tests = {
        list->next,
    };

    const std::vector<ListNode *> expected = {
        createList({4, 1, 9}),
    };

    int i = 0;
    for (auto test : tests)
    {
        printList(list);
        sol.deleteNode(test);
        assert(equal(list, expected[i]));
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}