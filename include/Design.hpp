#ifndef DESIGN_HPP
#define DESIGN_HPP

#include <vector>
// #include <unordered_set>

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

// class WordDictionary {
// public:
//     /** Initialize your data structure here. */
//     WordDictionary() {
        
//     }
    
//     /** Adds a word into the data structure. */
//     void addWord(std::string word) {
        
//     }
    
//     /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
//     bool search(std::string word) {
        
//     }

// private:
// };

class SubrectangleQueries {
public:
    SubrectangleQueries(std::vector<std::vector<int>>& rectangle): m_rect(rectangle) 
    {
        
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) 
    {
        if ((row1 > m_rect.size() || row1 < 0) ||
            (col1 > m_rect[0].size() || col1 < 0) ||
            (row2 > m_rect.size() || row2 < 0) ||
            (col2 > m_rect[0].size() || col2 < 0))
        {
            return;
        }

        for (int i = row1; i <= row2; ++i)
        {
            for (int j = col1; j <= col2; ++j)
            {
                m_rect[i][j] = newValue;
            }
        }
    }
    
    int getValue(int row, int col) 
    {
        if ((row > m_rect.size() || row < 0) ||
            (col > m_rect[0].size() || col < 0))
        {
            return -1;
        }

        return m_rect[row][col];
    }

private:
    std::vector<std::vector<int>> m_rect;

};

#endif // DESIGN_HPP