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
#include <bitset>

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

struct Range
{
    int lower;
    int upper;
};

Range get_range(const std::string& rule)
{
    Range r;
    r.lower = std::stoi(rule.substr(0, rule.find("-")));
    r.upper = std::stoi(rule.substr(rule.find("-") + 1));

    return r;
}

void get_rules(const std::vector<std::string>& lines, std::vector<Range>& ranges)
{
    int counter = 0;
    for (auto line: lines)
    {
        if (line == "")
            break;

        Range r1, r2;
        std::string rules = line.substr(line.find(":") + 1);
        std::string rule1 = rules.substr(0, rules.find("or") - 1);
        std::string rule2 = rules.substr(rules.find("or") + 2);
        r1 = get_range(rule1);
        r2 = get_range(rule2);
        ranges.push_back(r1);
        ranges.push_back(r2);

        counter++;
    }

    std::cout << "Rules: " << counter << std::endl;
}

struct Ticket 
{
    std::vector<int> values;
};

std::vector<int> get_ticket_values(const std::string& line)
{
    std::vector<int> ticket_values;

    std::string l = line;
    while (true)
    {
        auto value = (l.substr(0, l.find(",")));
        auto valueInt = std::stoi(value);
        auto pos = l.find(",");

        ticket_values.push_back(valueInt);
        if (pos == std::string::npos)
            break;

        l = l.substr(pos + 1);
    }

    return ticket_values;
}

void get_tickets(const std::vector<std::string>& lines, std::vector<Ticket>& tickets)
{
    bool foundTickets = false;
    for (auto line: lines)
    {
        if (line == "nearby tickets:")
        {
            foundTickets = true;
            continue;
        }

        if (foundTickets)
        {
            Ticket ticket;
            ticket.values = get_ticket_values(line);
            tickets.push_back(ticket);
        }
    }
}

bool is_valid_value(const std::vector<Range>& ranges, int value)
{
    bool valid = false;

    for (auto range: ranges)
    {
        if (value >= range.lower && value <= range.upper)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

std::vector<int> get_invalid_values(const std::vector<Range>& ranges, const std::vector<Ticket>& tickets)
{
    std::vector<int> invalid_values;
    for (auto ticket: tickets)
    {
        for (auto value: ticket.values)
        {
            if (!is_valid_value(ranges, value))
            {
                invalid_values.push_back(value);
            }
        }
    }

    return invalid_values;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day16.txt");
    std::vector<Range> ranges;
    std::vector<Ticket> tickets;

    get_rules(lines, ranges);
    get_tickets(lines, tickets);
    std::vector<int> invalid_values = get_invalid_values(ranges, tickets);

    std::cout << "Sum: " << std::accumulate(invalid_values.begin(), invalid_values.end(), 0) << std::endl;
    for (auto value: invalid_values)
    {
        // std::cout << value << std::endl;
    }
    std::cout << "First: " << invalid_values.size() << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}