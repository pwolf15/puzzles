#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

std::vector<std::string> get_lines(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return lines;
    }

    std::string line;
    while (getline(infile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> parse_buses(std::string line) 
{
    std::vector<std::string> buses;

    std::string currentId;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ',')
        {
            buses.push_back(currentId);
            currentId = "";
        }
        else
        {
            currentId += line[i];
        }
    }

    buses.push_back(currentId);

    return buses;
}

void get_start_time(std::vector<int> buses, long long earliest)
{
    int start = earliest;
    while (true) 
    {
        for (auto bus: buses)
        {
            if (earliest % bus == 0)
            {
                std::cout << "earliest: " << earliest << std::endl;
                std::cout << "bus: " << bus << std::endl;
                std::cout << "product: " << (earliest - start) * bus << std::endl;
                return;
            }
        }

        earliest++;
    }
}

void get_earliest(std::vector<std::string> buses) 
{
    std::vector<long long> busIds;
    std::vector<long long> distances;

    int distance = 0;
    for (int i = 0; i < buses.size(); ++i)
    {
        std::string bus = buses[i];
        if (bus != "x")
        {
            busIds.push_back(std::stoi(bus));
            distances.push_back(i);
        }
    }

    for (size_t i = 0; i < busIds.size(); i++)
    {
        std::cout << "bus: " << busIds[i] << ", distance: " << distances[i] << std::endl;
    }

    long long startTime = busIds[0];
    long long largestId = busIds[0];
    int largestDistance = 0;
    for (int i = 1; i < busIds.size(); ++i)
    {
        if (busIds[i] > largestId)
        {
            largestId = busIds[i];
            largestDistance = distances[i];
        }
    }

    std::cout << "largest id: " << largestId << std::endl;
    std::cout << "largext distance: " << largestDistance << std::endl;

    long long mult = largestId;
    while (true)
    {
        bool matchFound = true;
        long long startTime = mult - largestDistance;
        for (int i = 0; i < busIds.size(); ++i)
        {
            if (((startTime + distances[i]) % busIds[i]) != 0)
            {
                matchFound = false;
                break;
            }
        }

        if (matchFound)
        {
            std::cout << "Mult:" << mult << std::endl;
            std::cout << "start time: " << startTime << std::endl;
            return;
        }

        if (startTime % 1202161486 == 0)
        {
            std::cout << startTime << std::endl;
        }

        mult += largestId;
    }
}

int main()
{
    std::vector<std::string> lines = get_lines("../day13.txt");
    long long startTime = std::stoi(lines[0]);
    std::vector<std::string> buses = parse_buses(lines[1]);
    std::vector<std::string> busIds;
    std::copy_if(buses.begin(), buses.end(), std::back_inserter(busIds), [](std::string bus) {
        return bus != "x";
    });

    std::vector<int> bus_ids_nums;
    std::transform(busIds.begin(), busIds.end(), std::back_inserter(bus_ids_nums), [](std::string busId) {
        return std::stoi(busId);
    });

    for (auto bus: bus_ids_nums) 
    {
        std::cout << bus << std::endl;
    }

    get_start_time(bus_ids_nums, startTime);
    get_earliest(buses);

    std::cout << "Start time: " << startTime << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}