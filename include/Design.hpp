#ifndef DESIGN_HPP
#define DESIGN_HPP

#include <vector>

class ShuffledArray {
public:
    ShuffledArray(std::vector<int>& nums);
    
    /** Resets the array to its original configuration and return it. */
    std::vector<int> reset();
    
    /** Returns a random shuffling of the array. */
    std::vector<int> shuffle();

private:
    std::vector<int> m_nums;
    std::vector<int> m_nums_backup;
};

class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        store.resize(1e6);
        std::fill(store.begin(), store.end(), 0);
    }
    
    void add(int key) {
        store[key] = 1;
    }
    
    void remove(int key) {
        store[key] = 0;
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return store[key] != 0;
    }
private:
    std::vector<int> store;
};

#endif // DESIGN_HPP