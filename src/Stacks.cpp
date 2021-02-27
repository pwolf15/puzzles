#include "Stacks.hpp"

#include <stack>
#include <iostream>

void PrintLinkedListInReverse(std::shared_ptr<ListNodeEPI<int>> head)
{
    std::stack<int> nodes;
    while (head) {
        nodes.push(head->data);
        head = head->next;
    }
    while (!empty(nodes)) {
        std::cout << nodes.top() << std::endl;
        nodes.pop();
    }
}