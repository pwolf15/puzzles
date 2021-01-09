#include "Recursion.hpp"

long long Gcd(long long x, long long y) 
{
    return y == 0 ? x : Gcd(y, x % y);
}