#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <unordered_set>

using namespace std;

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
                std::cout << randomizedContainer.size() << std::endl;
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (setImpl.find(val) == setImpl.end())
        {
            setImpl.insert(val);
            randomizedContainer.push_back(setImpl.find(val));
                    std::cout << "size: " << randomizedContainer.size() << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto iter = setImpl.find(val);
        if (iter != setImpl.end())
        {
            randomizedContainer.erase(std::find(randomizedContainer.begin(), randomizedContainer.end(), iter));
            setImpl.erase(val);
            return true;
        }
        else
        {
            return false;
        } 
    }
    
    /** Get a random element from the set. */
    int getRandom() 
    {
        int a = rand() % randomizedContainer.size();
        return *randomizedContainer[a];
    }

private:
    std::unordered_set<int> setImpl;
    std::vector<std::unordered_set<int>::iterator> randomizedContainer;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main()
{

    RandomizedSet set;
    srand (time(NULL));
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.insert(5);

    for (int i = 0; i < 10; i++)
    {
        std::cout << set.getRandom() << std::endl;
    }
    
    set.remove(1);
    set.remove(2);
    set.remove(3);

    std::cout << "Removing" << std::endl;
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << set.getRandom() << std::endl;
    }

    return 0;
}