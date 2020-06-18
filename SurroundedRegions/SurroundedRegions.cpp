#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>
#include <set>

using namespace std;

class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        std::set<std::pair<int, int>> eliminatedSquares;
        std::set<std::pair<int, int>> restoreSquares;
        for (auto i = 0; i < board.size(); i++)
        {
            for (auto j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == 'O')
                {
                    if 
                    (
                        (i == 0) || (j == 0) || (i == board.size() - 1) || (j == board[0].size() - 1)
                    )
                    {
                        restoreSquares.insert({i, j});
                    }
                    else
                    {
                        board[i][j] = 'X';
                        eliminatedSquares.insert({i, j});
                    }
                }
            }
        }

        for (auto square: restoreSquares)
        {
            restoreNeighbors(square.first, square.second, eliminatedSquares, board);
        }
    }
private:
    std::set<std::pair<int, int>> restoreNeighbors(int i, int j, std::set<std::pair<int, int>>& squares, vector<vector<char>> &board)
    {

        std::set<std::pair<int, int>> restored;
        for (auto s: squares)
        {
            if 
            (
                ((abs(i - s.first) == 1) && j == s.second) ||
                ((i == s.first) && (abs(j - s.second) == 1))
            )
            {
                
                restored.insert(s);
                squares.erase(s);
                board[s.first][s.second] = 'O';
            }

        }
        for (auto r: restored)
        {
            auto newRestored = restoreNeighbors(r.first, r.second, squares, board);
            restored.insert(newRestored.begin(), newRestored.end());
        }

        return restored;
    }
};

void print(const vector<vector<char>> &board)
{
    for (auto i = 0; i < board.size(); i++)
    {
        for (auto j = 0; j < board[0].size(); j++)
        {
            std::cout << board[i][j] << " ";
        }

        std::cout << "\n";
    }
}

void compareBoards(const vector<vector<char>> &board1, const vector<vector<char>> &board2)
{
    for (int i = 0; i < board1.size(); i++) 
    {
        for (int j = 0; j < board1[i].size(); j++)
        {
            if (board1[i][j] != board2[i][j])
            {
                std::cout << i << ", " << j << std::endl;
            }
        }
    }
}

int main()
{

    Solution sol;

    vector<vector<char>> board =
        {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'},
        };

    sol.solve(board);
    print(board);

    vector<vector<char>> board2 =
    {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
    };

    sol.solve(board2);
    print(board2);

    vector<vector<char>> board3 =
    {
        {'O','X','O','O','X','X'},
        {'O','X','X','X','O','X'},
        {'X','O','O','X','O','O'},
        {'X','O','X','X','X','X'},
        {'O','O','X','O','X','X'},
        {'X','X','O','O','O','O'},
    };

    sol.solve(board3);
    print(board3);

    vector<vector<char>> board5 =
    {
        {'O','X','O','O','X','X'},
        {'O','X','X','X','O','X'},
        {'X','X','X','X','O','O'},
        {'X','X','X','X','X','X'},
        {'O','O','X','O','X','X'},
        {'X','X','O','O','O','O'},
    };

    vector<vector<char>> board4 =
    {
        {'O','X','O','O','X','X'},
        {'O','X','X','X','O','X'},
        {'X','O','O','X','O','O'},
        {'X','O','X','X','X','X'},
        {'O','O','X','O','X','X'},
        {'X','X','O','O','O','O'},
    };

    vector<vector<char>> board10 =
    {
        {'O','X','O','O','X','X','X','O','O','O','O','O','X','O','O','O','O','X','O','X'},
        {'X','O','X','O','O','X','X','O','O','X','O','X','O','X','O','X','X','O','O','O'},
        {'O','X','O','O','O','X','X','X','X','O','O','O','O','O','X','X','X','X','O','X'},
        {'X','X','O','O','O','X','X','O','O','O','X','X','X','O','O','X','O','X','X','O'},
        {'O','X','O','X','X','O','X','O','O','O','X','O','O','X','O','O','O','O','O','X'},
        {'X','O','O','X','O','X','O','O','O','X','X','O','X','O','O','X','O','O','O','O'},
        {'X','O','O','O','X','X','O','O','O','O','O','X','O','O','X','O','O','O','O','X'},
        {'X','O','O','O','X','O','X','X','X','O','X','O','X','X','X','X','O','O','O','X'},
        {'X','O','O','X','O','O','O','X','O','O','O','O','O','O','O','O','O','X','O','X'},
        {'O','O','O','X','O','X','X','X','X','X','X','X','X','X','O','O','O','O','X','O'},
        {'X','O','X','O','X','O','O','X','X','X','O','X','X','O','O','X','X','O','O','O'},
        {'O','X','O','O','X','O','O','O','O','O','O','X','X','X','X','O','O','O','X','O'},
        {'X','O','O','O','X','X','X','O','X','O','O','O','X','O','X','O','X','O','O','X'},
        {'O','O','O','O','X','O','X','X','O','X','O','X','O','X','X','X','X','O','O','O'},
        {'O','X','X','O','O','O','O','X','O','O','X','X','X','O','O','X','X','O','X','O'},
        {'X','O','X','X','X','X','X','X','O','X','X','O','X','O','O','X','O','O','O','X'},
        {'X','O','O','O','X','O','X','O','O','X','O','X','O','O','X','O','O','X','X','X'},
        {'O','O','X','O','O','O','O','X','O','O','X','X','O','X','X','X','O','O','O','O'},
        {'O','O','X','O','O','O','O','O','O','X','X','O','X','O','X','O','O','O','X','X'},
        {'X','O','O','O','X','O','X','X','X','O','O','X','O','X','O','X','X','O','O','O'},
    };
    
    vector<vector<char>> board11 =
    {
        {'O','X','O','O','X','X','X','O','O','O','O','O','X','O','O','O','O','X','O','X'},
        {'X','X','X','O','O','X','X','O','O','X','O','X','O','X','O','X','X','O','O','O'},
        {'O','X','O','O','O','X','X','X','X','O','O','O','O','O','X','X','X','X','O','X'},
        {'X','X','O','O','O','X','X','O','O','O','X','X','X','O','O','X','O','X','X','O'},
        {'O','X','O','X','X','X','X','O','O','O','X','X','X','X','O','O','O','O','O','X'},
        {'X','O','O','X','X','X','O','O','O','X','X','X','X','O','O','X','O','O','O','O'},
        {'X','O','O','O','X','X','O','O','O','O','O','X','O','O','X','O','O','O','O','X'},
        {'X','O','O','O','X','X','X','X','X','O','X','O','X','X','X','X','O','O','O','X'},
        {'X','O','O','X','X','X','X','X','O','O','O','O','O','O','O','O','O','X','O','X'},
        {'O','O','O','X','X','X','X','X','X','X','X','X','X','X','O','O','O','O','X','O'},
        {'X','O','X','O','X','X','X','X','X','X','X','X','X','O','O','X','X','O','O','O'},
        {'O','X','O','O','X','X','X','X','X','X','X','X','X','X','X','O','O','O','X','O'},
        {'X','O','O','O','X','X','X','X','X','X','X','X','X','X','X','O','X','O','O','X'},
        {'O','O','O','O','X','O','X','X','O','X','X','X','X','X','X','X','X','O','O','O'},
        {'O','X','X','O','O','O','O','X','O','O','X','X','X','X','X','X','X','O','X','O'},
        {'X','O','X','X','X','X','X','X','O','X','X','X','X','X','X','X','O','O','X','X'},
        {'X','O','O','O','X','O','X','O','O','X','X','X','X','X','X','O','O','X','X','X'},
        {'O','O','X','O','O','O','O','X','O','O','X','X','X','X','X','X','O','O','O','O'},
        {'O','O','X','O','O','O','O','O','O','X','X','X','X','X','X','O','O','O','X','X'},
        {'X','O','O','O','X','O','X','X','X','O','O','X','O','X','O','X','X','O','O','O'}
    };

    vector<vector<char>> board12 = 
    {
        {'O','X','O','O','X','X','X','O','O','O','O','O','X','O','O','O','O','X','O','X'},
        {'X','X','X','O','O','X','X','O','O','X','O','X','O','X','O','X','X','O','O','O'},
        {'O','X','O','O','O','X','X','X','X','O','O','O','O','O','X','X','X','X','O','X'},
        {'X','X','O','O','O','X','X','O','O','O','X','X','X','O','O','X','O','X','X','O'},
        {'O','X','O','X','X','X','X','O','O','O','X','X','X','X','O','O','O','O','O','X'},
        {'X','O','O','X','X','X','O','O','O','X','X','X','X','O','O','X','O','O','O','O'},
        {'X','O','O','O','X','X','O','O','O','O','O','X','O','O','X','O','O','O','O','X'},
        {'X','O','O','O','X','X','X','X','X','O','X','O','X','X','X','X','O','O','O','X'},
        {'X','O','O','X','X','X','X','X','O','O','O','O','O','O','O','O','O','X','O','X'},
        {'O','O','O','X','X','X','X','X','X','X','X','X','X','X','O','O','O','O','X','O'},
        {'X','O','X','O','X','X','X','X','X','X','X','X','X','O','O','X','X','O','O','O'},
        {'O','X','O','O','X','X','X','X','X','X','X','X','X','X','X','O','O','O','X','O'},
        {'X','O','O','O','X','X','X','X','X','X','X','X','X','X','X','O','X','O','O','X'},
        {'O','O','O','O','X','O','X','X','O','X','X','X','X','X','X','X','X','O','O','O'},
        {'O','X','X','O','O','O','O','X','O','O','X','X','X','X','X','X','X','O','X','O'},
        {'X','O','X','X','X','X','X','X','O','X','X','X','X','X','X','X','O','O','O','X'},
        {'X','O','O','O','X','O','X','O','O','X','X','X','X','X','X','O','O','X','X','X'},
        {'O','O','X','O','O','O','O','X','O','O','X','X','X','X','X','X','O','O','O','O'},
        {'O','O','X','O','O','O','O','O','O','X','X','X','X','X','X','O','O','O','X','X'},
        {'X','O','O','O','X','O','X','X','X','O','O','X','O','X','O','X','X','O','O','O'},
    };

    sol.solve(board10);
    compareBoards(board10, board12);

    return 0;
}