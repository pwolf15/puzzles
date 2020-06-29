#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        auto sortLambda = [](std::vector<string> a, std::vector<string> b) {

            return a[1] <= b[1];
        };

        std::sort(tickets.begin(), tickets.end(), sortLambda);
        
        std::vector<std::string> stops = {};

        std::string searchStart = "JFK";
        int i = 0;
        while (true) 
        {
            if (tickets.empty())
            {
                stops.push_back(searchStart);
                break;
            }

            auto ticket = tickets[i];
            if (searchStart == ticket[0] && findDest(ticket[1], tickets))
            {
                stops.push_back(searchStart);
                searchStart = ticket[1];
                tickets.erase(tickets.begin() + i);
                i = 0;

                continue;
            }
            else
            {
                i++;
            }
        }

        return stops;
    }

bool findDest(std::string dest, std::vector<std::vector<std::string>> tickets)
{
    if (tickets.size() == 1)
    {
        return true;
    }
    for (auto i = 0; i < tickets.size(); ++i)
    {
        if (dest == tickets[i][0])
        {
            return true;
        }
    }

    return false;
}
};


int main()
{

    Solution sol;

    std::vector<std::vector<std::string>> tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    auto itin = sol.findItinerary(tickets);
    for (auto stop: itin)
    {
        std::cout << stop << std::endl;
    }
    std::cout << "\n\n";
    tickets = {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    itin = sol.findItinerary(tickets);
    for (auto stop: itin)
    {
        std::cout << stop << std::endl;
    }
    std::cout << "\n\n";
    tickets = {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    itin = sol.findItinerary(tickets);
    for (auto stop: itin)
    {
        std::cout << stop << std::endl;
    }

    return 0;
}