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
#include <map>
#include <regex>

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

std::unordered_map<int, std::string> generate_regexes(std::vector<std::string> regex_lines)
{
    std::unordered_map<int, std::string> regexes;
    while (regexes.size() != regex_lines.size())
    {
        for (auto regex_line: regex_lines)
        {
            int regex_num = std::stoi(regex_line.substr(0, regex_line.find(":")));
            std::string rules = regex_line.substr(regex_line.find(":") + 1);
            
            if (rules.find("\"") != std::string::npos)
            {
                // std::cout << rules << std::endl;

                int ruleStart = rules.find("\"") + 1;
                int ruleSize   = rules.substr(ruleStart).find("\"");
                // std::cout << ruleSize << std::endl;
                regexes[regex_num] = rules.substr(ruleStart, ruleSize);
                // std::cout << regexes[regex_num] << std::endl;
            }
            else
            {
                std::string num_str = "";
                bool in_num = false;
                bool undefined_rule = false;
                bool need_paren = false;
                std::string regex_str = "";

                for (int i = 0; i < rules.size(); ++i)
                {
                    if (undefined_rule)
                    {
                        break;
                    }

                    if (rules[i] == ' ')
                    {
                        if (in_num)
                        {
                            in_num = false;
                            int rule_num = std::stoi(num_str);
                            if (regexes.find(rule_num) == regexes.end())
                            {
                                undefined_rule = true;
                            }
                            else
                            {
                                std::string sub_regex = regexes[rule_num];
                                if (sub_regex.find("|") != std::string::npos) 
                                {
                                    sub_regex = "(" + sub_regex + ")";
                                }
                                regex_str += sub_regex;
                            }

                            num_str = "";
                        }
                        continue;
                    }
                    else if (rules[i] == '|')
                    {
                        if (in_num)
                        {
                            in_num = false;
                            int rule_num = std::stoi(num_str);
                            if (regexes.find(rule_num) == regexes.end())
                            {
                                undefined_rule = true;
                            }
                            else
                            {
                                std::string sub_regex = regexes[rule_num];
                                if (sub_regex.find("|") != std::string::npos) 
                                {
                                    sub_regex = "(" + sub_regex + ")";
                                }
                                regex_str += sub_regex;
                            }

                            num_str = "";
                        }

                        regex_str = "(" + regex_str + ")";
                        regex_str += "|";
                        regex_str += "(";
                        need_paren = true;
                        continue;
                    }
                    else if (isdigit(rules[i]))
                    {
                        if (!in_num)
                        {
                            in_num = true;
                        }

                        num_str += rules[i];
                    }
                }

                if (in_num)
                {
                    in_num = false;
                    int rule_num = std::stoi(num_str);
                    if (regexes.find(rule_num) == regexes.end())
                    {
                        undefined_rule = true;
                    }
                    else
                    {
                        std::string sub_regex = regexes[rule_num];
                        if (sub_regex.find("|") != std::string::npos) 
                        {
                            sub_regex = "(" + sub_regex + ")";
                        }
                        regex_str += sub_regex;
                    }

                    num_str = "";
                }

                if (need_paren)
                {
                    regex_str += ")";
                }

                if (!undefined_rule)
                {
                    regexes[regex_num] = regex_str;
                }
            }
        }
    }

    std::cout << "Regexes: " << regexes.size() << std::endl;
    for (auto regexPair: regexes)
    {
        std::cout << "regex[" << regexPair.first << "]: " << regexPair.second << std::endl;
    }

    return regexes;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day19.txt");
    std::vector<std::string> regex_lines;
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(regex_lines), [](std::string line) {

        if (line.find(":") != std::string::npos)
        {
            return true;
        }

        return false;
    });

    std::vector<std::string> strs;
    for (int i = regex_lines.size() + 1; i < lines.size(); ++i)
    {
        strs.push_back(lines[i]);
    }

    std::unordered_map<int, std::string> regexes = generate_regexes(regex_lines);

    std::vector<std::string> tests = {
        "aaaabb",
        "aaabab",
        "abbabb",
        "abbbab",
        "aabaab",
        "aabbbb",
        "abaaab",
        "ababbb",
        "ab"
    };

    std::string regex_0 = regexes[0];
    int count = 0;
    for (auto str: strs)
    {
        if (std::regex_match (str, std::regex(regex_0)))
        {
            std::cout << "string literal matched\n";
            count++;
        }
        else
        {
            std::cout << "string literal not matched\n";
        }
    }

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num strs: " << strs.size() << std::endl;
    std::cout << "Regexes: " << regexes.size() << std::endl;
    std::cout << "Num matching: " << count << std::endl;

    return 0;
}