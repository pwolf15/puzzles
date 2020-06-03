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
class Solution {
public:
    bool hasCycle(ListNode *head) {
        auto target = head;
        head = head->next;
        while (true)
        {
            if (head == nullptr)
            {
                return false;
            }
            else if (head == target)
            {
                return true;
            }
            else 
            {
                head = head->next;
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

    auto list1 = createList({3,2,0,-4});
    auto cur = list1;
    auto target = cur->next;
    while (true) 
    {
        if (cur->next == nullptr)
        {
            cur->next = target;
            break;
        }
        else
        {
            cur = cur->next;
        }
    }

    const std::vector<ListNode *> tests = {
        list1->next,
    };

    const std::vector<bool> expected = {
        true
    };

    int i = 0;
    for (auto test : tests)
    {
        bool result = sol.hasCycle(test);
        assert(expected[i] == result);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}