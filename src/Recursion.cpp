#include "Recursion.hpp"

// O(log max(x, y)) or O(n) where n is number of bits needed to reprsent inputs
// space complexity: O(n) (maximum depth of call stack)
long long Gcd(long long x, long long y) 
{
    return y == 0 ? x : Gcd(y, x % y);
}