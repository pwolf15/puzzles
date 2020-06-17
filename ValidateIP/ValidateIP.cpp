#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

class Solution {
public:
string validIPAddress(string IP) {
        regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");   
        std::string result = "Neither";
        if(regex_match(IP, ipv4))
        {
            result = "IPv4";
        }    
        else if(regex_match(IP, ipv6)) 
        {
            result = "IPv6";
        }
            
        return result;
    }
};


int main()
{

    Solution sol;

    std::cout << sol.validIPAddress("") << std::endl;
    std::cout << sol.validIPAddress("172.16.254.1") << std::endl;
    std::cout << sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334") << std::endl;
    std::cout << sol.validIPAddress("256.256.256.256") << std::endl;

    return 0;
}