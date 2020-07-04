#include <iostream>
#include <vector>
#include <math.h>


class Solution {
public:
    std::vector<int> prisonAfterNDays(std::vector<int>& cells, int N) {
        
        if (!init)
        {
            cache.resize(pow(2, 8));

            for (int i = 0; i < cache.size(); i++)
            {
                cache[i] = getNextCells(i);
            }

            init = true;
        }

        // map from cells to sequence number
        std::vector<int> cellsToSeqNum;

        // keep track of current sequence
        // if cycle found, can break from search (similar to fixed point)
        std::vector<int> seq;

        for (int i = 0; i < pow(2, 8); i++)
        {
            cellsToSeqNum.push_back(0);
        }
        
        // keep track of sequence
        int seqNum = 0;

        // keep track of cur and prev cell configs
        int prevCells = 0;
        int curCells = getInt(cells);

        #ifdef LOGS
        std::cout << "Cur cells: " << curCells << std::endl;
        #endif

        for (auto i = 0; i < N; i++)
        {
            // add current cell to sequence
            seq.push_back(curCells);
            cellsToSeqNum[curCells] = seqNum;

            #ifdef LOGS
            std::cout << "Current cell[" << seqNum << "]: " << curCells << "\n";
            #endif

            // get next day's cells
            prevCells = curCells;
            curCells = cache[curCells];

            seqNum++;

            if (cellsToSeqNum[curCells])
            {
                // found cycle
                int cycleStart = cellsToSeqNum[curCells];
                int cycleEnd = cellsToSeqNum[prevCells];

                #ifdef LOGS
                std::cout << "Cycle start = " << cycleStart << "\n";
                std::cout << "Cycle end = " << cycleEnd << "\n";
                #endif

                int cycleSize = cycleEnd - cycleStart + 1;
                int index = (N - 1) % cycleSize + cycleStart;
                curCells = seq[index];
                break;
            }
        }

        return getVec(curCells);
    }

    // cache all (2^8) cell results
    bool init = false;
    std::vector<int> cache;

    // get next set of cells given current day's
    int getNextCells(int val)
    {
        int result = 0;
        for (auto j = 0; j < 8; j++)
        {
            if ((j > 0 && j < 7) && !(((val >> (7 - (j - 1))) & 1) ^ ((val >> (7 - (j + 1))) & 1)))
            {
                result |= (1 << (7 - j));
            }
            else
            {
                result &= ~(1 << (7 - j));
            }
        }

        return result;
    }

    // get integer representation of cells
    int getInt(std::vector<int> cells)
    {
        int mask = 0x00;
        for (auto i = 0; i < 8; i++)
        {
            mask |= (cells[i] << (7 - i));
        }

        return mask;
    }

    // get vector representation of cells
    std::vector<int> getVec(int vals)
    {
        std::vector<int> cells;
        for (int i = 0; i < 8; i++)
        {
            cells.push_back((vals >> (7 - i)) & 0x1);
        }

        return cells;
    }
};

int main()
{
    Solution sol;
    std::vector<int> inCells = {0,1,0,1,1,0,0,1};
    auto outCells = sol.prisonAfterNDays(inCells, 7);
    std::cout << "Int: " << sol.getNextCells(sol.getInt(inCells)) << std::endl;
    for (auto cell: outCells)
    {
        std::cout << cell << std::endl;
    }
    inCells = {1,0,0,1,0,0,1,0};
    outCells = sol.prisonAfterNDays(inCells, 1000000000);

    std::cout << "\n";
    for (auto cell: outCells)
    {
        std::cout << cell << std::endl;
    }

    inCells = {1,1,0,1,1,0,1,1};
    outCells = sol.prisonAfterNDays(inCells, 6);

    std::cout << "\n";
    for (auto cell: outCells)
    {
        std::cout << cell << std::endl;
    }

    std::cout << sol.getNextCells(36) << std::endl;

    return 0;
}