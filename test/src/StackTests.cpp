#include "CppUTest/TestHarness.h"

#include "Stacks.hpp"
#include "LinkedLists.hpp"

TEST_GROUP(Stacks)
{
 
};

TEST(Stacks, PrintLinkedListInReverse)
{
    std::shared_ptr<ListNodeEPI<int>> l1 = createList({ 3, 1, 4 });
    PrintLinkedListInReverse(l1);
};
