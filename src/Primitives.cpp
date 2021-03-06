#include "Primitives.hpp"

#include <math.h>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <Arrays.hpp>

// Known as Digital Root
// below is basic logarithmic solution
// Given a non-negative integer num,
// repeatedly add all its digits until the result has only one digit.
// time complexity: O(log10(n))
int addDigits_log(int num)
{
    int result = 0;
    while (num)
    {
        // sum digits of num and move into result
        // if result greater than or equal to 10, start again
        result += num % 10;
        num /= 10;

        if (num == 0 && result >= 10)
        {
            num = result;
            result = 0;
        }
    }

    return result;
}

int addDigits_constant(int num)
{
    return num == 0 ? 0 : 1 + (num - 1) % 9;
}

int addDigits(int num)
{
    return addDigits_constant(num);
}

// Write a function that takes an unsigned integer and return the number of '1' bits it has
// (also known as the Hamming weight).
// redundant with EPI Count Bits
int hammingWeight(uint32_t n)
{
    int numBits = 0;
    while (n)
    {
        numBits += n & 1;
        n >>= 1;
    }

    return numBits;
}

bool isPowerOfThree(int n)
{
    long long powered = 0;
    bool powerOfThree = false;
    size_t i = 0;
    while (powered < n)
    {
        powered = pow(3, i);
        i++;

        if (powered == n)
        {
            powerOfThree = true;
            break;
        }
    }

    return powerOfThree;
}

int missingNumber(std::vector<int> &nums)
{

    int expectedSum = (nums.size() + 1) * (nums.size()) / 2;
    int actualSum = std::accumulate(nums.begin(), nums.end(), 0);
    return expectedSum - actualSum;
}

int countPrimes_BF(int n)
{
    auto isPrime = [](int n) {
        for (int i = 1; i < n; ++i)
        {
            if (n % i == 0 && i != 1)
            {
                return false;
            }
        }

        return true;
    };

    std::vector<int> primes;
    for (int i = 2; i < n; ++i)
    {
        if (isPrime(i))
        {
            primes.push_back(i);
        }
    }

    return primes.size();
}

int sieve(int n)
{
    std::vector<int> nums(n, 1);

    if (n < 2)
    {
        return 0;
    }
    
    for (int i = 2; i < n; ++i)
    {
        if (nums[i])
        {
            for (int j = i * 2; j < n; j += i)
            {
                nums[j] = 0;
            }
        }
    }

    int i = 0;
    nums[0] = 0;
    nums[1] = 0;

    auto result = std::count_if(nums.begin(), nums.end(), [](int n) {
        return n;
    });

    return result;
}

int countPrimes(int n)
{
    return sieve(n);
}

bool isPowerOfFour(int n)
{
    long long powered = 0;
    bool powerOfFour = false;
    size_t i = 0;
    while (powered < n)
    {
        powered = pow(4, i);
        i++;

        if (powered == n)
        {
            powerOfFour = true;
            break;
        }
    }

    return powerOfFour;
}

void magicSquare(int n)
{
    std::vector<int> grid;
    for (int i = 1; i <= n * n; ++i)
    {
        grid.push_back(i);
    }

    while(true)
    {
        std::random_shuffle ( grid.begin(), grid.end() );
        std::vector<int> sums;
        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            for (int j = 0; j < n; ++j)
            {
                sum += grid[i * n + j];
            }
            sums.push_back(sum);
        }

        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            for (int j = 0; j < n; ++j)
            {
                sum += grid[j * n + i];
            }
            sums.push_back(sum);
        }

        int sum = 0;
        for (int j = 0; j < n; ++j)
        {
            sum += grid[j * n + j];
        }

        sums.push_back(sum);  

        sum = 0;
        for (int j = 0; j < n; ++j)
        {
            sum += grid[j * n + n - j - 1];
        }
        sums.push_back(sum);

        std::set<int> sumsUnique;
        for (auto sum: sums)
        {
            sumsUnique.insert(sum);
        }

        if (sumsUnique.size() == 1)
        {
            break;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << grid[i * n + j] << " ";
        }

        std::cout << "\n";
    }
}

short CountBits(unsigned int x) 
{
    int numBits = 0;
    while (x)
    {
        numBits += x & 1;
        x >>= 1;
    }

    return numBits;
}


int numSteps(int n)
{
    int num_steps = 0;
    while (n)
    {
        num_steps++;
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n -= 1;
        }
    }

    return num_steps;
}

// time complexity: O(n / 2)
// space complexity: O(1)
bool checkPerfectNumber(int num)
{
    int sum = 0;
    for (int i = 1; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            int div1 = i;
            int div2 = num / i;

            if (div1 == 1 && div2 == num)
            {
                // only add 1, if num != 1
                if (div2 != div1)
                {
                    sum += 1;
                }
            }
            else if (div1 != div2)
            {
                // only add unique divisors
                sum += div1;
                sum += div2;
            }
            else
            {
                // if div1 == div2, only add div1
                sum += div1;
            }
        }
    }

    return sum == num;
}

// time complexity: O(log n)
// space complexity: O(1)
int binaryGap(int n)
{
    int maxDistance = 0;
    int curDistance = 0;
    int lastOne     = -1;
    int index       = 0;
    while (n)
    {
        if (n % 2) 
        {
            if (lastOne == -1) 
            {
                lastOne = index;
            }
            else 
            {
                curDistance = (index - lastOne);
                lastOne = index;
                maxDistance = std::max(maxDistance, curDistance);
            }
        }

        n /= 2;
        index++;
    }

    return maxDistance;
}

// time complexity: O(1)
// space complexity: O(1)
bool hasAlternatingBits(int n)
{
    bool alternates = true;
    int prevBit = n % 2;
    n /= 2;
    while (n)
    {
        if (n % 2 == prevBit)
        {
            alternates = false;
            break;
        }

        prevBit = n % 2;
        n /= 2;
    }

    return alternates;
}

std::vector<std::string> readBinaryWatch(int num)
{
    return {};
}

// time complexity: O(n)
// space complexity: O(1)
int totalMoney(int n)
{
    int sum = 0;
    int numWeeks = n / 5;
    for (int i = 0; i <= numWeeks; ++i)
    {
        for (int j = i + 1; j <= i + 7 && j <= n; ++j)
        {
            sum += j;
        }

        n -= 6;
    }

    return sum;
}

// time complexity: O(N), where N number of bits
// space complexity: O(1)
int bitwiseComplement(int N)
{
    bool foundLeadingZero = false;

    if (!N) return 1;

    for (int i = (sizeof(int) * 8) - 1; i >= 0; --i)
    {
        if (foundLeadingZero)
        {
            N = ((1 << i) & ~N) | (~(1 << i) & N);
        }
        else if ((N >> i) & 0x1)
        {
            foundLeadingZero = true;
            N = ((1 << i) & ~N) | (~(1 << i) & N);
        }
    }

    return N;
}

// time complexity: O(n / 2 * log n), contains zero check requires iterating each digit
// space complexity: O(1)
std::vector<int> getNoZeroIntegers(int n)
{
    std::vector<int> result;
    auto containsZero = [](int n) {
        while (n)
        {
            if (n % 10 == 0)
            {
                return true;
            }

            n -= n % 10;
            n /= 10;
        }

        return false;
    };

    for (int i = 1; i <= n / 2; ++i)
    {
        if (containsZero(i))
        {
            continue;
        }
        else if (containsZero(n - i))
        {
            continue;
        }
        else
        {
            result.push_back(i);
            result.push_back(n - i);
            return result;
        }
    }

    return result;
}

// time complexity: O(1)
// space complexity: O(1)
int countOdds(int low, int high)
{
    // num odds
    // 13, 14, 15, 16, 17, 18 => 3
    // 12, 13, 14, 15, 16, 17 => 3
    // 11, 12
    // 11
    // 

    // if count is even, count == diff over two
    // if count is odd, 
    int count = high - low + 1;
    if (count % 2 == 0)
    {
        return count / 2;
    }
    else
    {
        return (low % 2 == 1) + (high - low) / 2;
    }
}

// time complexity: O(log n)
// space complexity: O(1)
int numberOfMatches(int n)
{
    int numMatches = 0;
    while (n > 1)
    {
        if (n % 2 == 1)
        {
            numMatches += n / 2;
            n /= 2;
            n += 1; // randomly advanced player
        }
        else 
        {
            numMatches += n / 2;
            n /= 2;
        }
    }
    return numMatches;
}

std::string dayOfTheWeek(int day, int month, int year)
{
    // Zeller's formula
    std::vector<std::string> days= {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int d = day, m = month, y = year, c;
    if (m < 3) m += 12, y -= 1;
    c = y / 100, y = y % 100;
    int w = (c / 4 - 2 * c + y + y / 4 + 13 * (m + 1) / 5 + d - 1) % 7;
    return days[(w + 7) % 7];
}

// time complexity: O(1)
// space complexity: O(1)
int dayOfYear(std::string date)
{
    int day = 0;
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayOfMonthStr = date.substr(8, 2);
    int year = std::stoi(yearStr), month = std::stoi(monthStr), dayOfMonth = std::stoi(dayOfMonthStr);

    std::vector<int> numDays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && ((year % 100 == 0 && year % 400 == 0) || year % 100 != 0)) numDays[1] += 1;
    for (int i = 1; i < month; ++i)
    {
        day += numDays[i - 1];
    }

    day += dayOfMonth;

    return day;
}

// time complexity: O(1)
// space complexity: O(1)
bool divisorGame(int N)
{
    return N % 2 == 0;
}

// time complexity: O(n)
// space complexity: O(n)
int countLargestGroup(int n)
{
    std::map<int, int> groups;
    auto computeSum = [](int n) {
        int sum = 0;
        while (n) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    };

    for (int i = 1; i <= n; i++)
    {
        int sum = computeSum(i);
        groups[sum]++;
    }

    std::map<int, int> group_counts;
    for (auto pair: groups)
    {
        group_counts[pair.second]++;
    }


    return group_counts.rbegin()->second;
}

int trailingZeroes(int n)
{
    std::function<int(int)> fact = [&](int n) {
        if (n == 1 || n == 0) return 1;
        return n * fact(n - 1);
    };

    int numTrailingZeroes = 0;
    long long val = fact(n);
    while (val) 
    {
        if (val % 10 != 0) 
        {
            break;
        }
        else
        {
            numTrailingZeroes++;
        }
        val /= 10;
    }
    return numTrailingZeroes;
}


// time complexity: O(n), compute each n only once
// space complexity: O(n + n), n for recursive solution and n for cache
int fibHelper(int n, std::unordered_map<int, int>& memoized_fib)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        int fib1 = 0, fib2 = 0;
        if (memoized_fib.find(n - 1) != memoized_fib.end())
        {
            fib1 = memoized_fib[n - 1];
        }
        else
        {
            fib1 = fibHelper(n - 1, memoized_fib);
            memoized_fib[n - 1] = fib1;
        }

        if (memoized_fib.find(n - 2) != memoized_fib.end())
        {
            fib2 = memoized_fib[n - 2];
        }
        else
        {
            fib2 = fibHelper(n - 2, memoized_fib);
            memoized_fib[n - 2] = fib2;
        }

        return fib1 + fib2;
    }
}

int fib(int n)
{
    std::unordered_map<int, int> memoized_fib;
    return fibHelper(n, memoized_fib);
}

std::vector<std::string> generateDeciBinary(int n)
{
    if (n <= 0) 
    {
        return { };
    }
    if (n == 1) 
    { 
        return { "0", "1" }; 
    }
    std::vector<std::string> ndb = generateDeciBinary(n - 1);
    std::vector<std::string> db;
    for (auto b: ndb)
    {
        db.push_back("1" + b);
    }
    for (auto b: ndb)
    {
        db.push_back("0" + b);
    }
    return db;
}

int getMin(std::vector<std::string> bin, std::vector<int>& cache, int n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;
    else {
        int min = std::numeric_limits<int>::max();
        for (int i = 0; i < bin.size(); ++i)
        {
            if (std::stoi(bin[i]) == 0) continue;

            int num = n - std::stoi(bin[i]);
            if (num >= 0 && num < cache.size())
            {
                if (cache[num] == -1)
                {
                    cache[num] = getMin(bin, cache, num);
                }
            }
            else
            {
                continue;
            }
                
            // std::cout << "min: " << min << std::endl;
            min = std::min(1 + cache[num], min);
        } 
        return min;
    }
}
int minPartitions_Helper(int n)
{
    std::vector<std::string> newDeciBinary = generateDeciBinary(5);
    for (auto b: newDeciBinary)
    {
        std::cout << "b: " << b << std::endl;
    }
    std::vector<int> cache(n + 1, -1);
    std::cout << "Min: " << getMin(newDeciBinary, cache, 87432) << std::endl;
    return getMin(newDeciBinary, cache, 32);
}

int minPartitions(std::string n)
{
    int nNum = std::stoi(n);
    return minPartitions_Helper(nNum);
}

// time complexity: O(1)
// space complexity: O(1)
bool isHappy(int n) 
{
    int arr[100] = { 0 };
    while (true)
    {
        int tmp = n;
        n = 0;
        
        while (tmp)
        {
            n += pow(tmp % 10, 2);
            tmp /= 10;
        }

        if (n == 1)
        {
            return n;
        }
        else if (n < 100 && arr[n] == 1)
        {
            return false;
        }
        else if (n < 100)
        {
            arr[n] = 1;
        }
    }

    return n == 1;
}

// time complexity: O(n)
// space complexity: O(1)
int findKthPositive(std::vector<int>& arr, int k)
{
    int i = 1;
    int j = 0;

    while (k)
    {
        if (j >= arr.size())
        {
            i++;
            k--;
            continue;
        }
        if (arr[j] > i)
        {
            k--;
            i++;
            continue;
        }

        j++;
        i++;
    }

    return i-1;
}

// time complexity: O(n)
// space complexity: O(1)s
int xorOperation(int n, int start)
{
    int result = 0;
    for (int i = 0; i < n; ++i)
    {
        result ^= 2*i + start;
    }
    return result;
}

// time complexity: O(log n)
// space complexity: O(1)
int subtractProductAndSum(int n)
{
    int sum = 0;
    int product = 1;
    while (n)
    {
        product *= n % 10;
        sum += n % 10;
        n /= 10;
    }

    return product - sum;
}

// time complexity: O(n)
// space complexity: O(1)
int maximum69Number (int num)
{
    int lastSix = -1;
    int digit = 0;
    int temp = num;
    while (temp)
    {
        if (temp % 10 == 6)
        {
            lastSix = digit;
        }

        temp /= 10;
        digit++;
    }

    if (lastSix != -1)
    {
        num += 3 * pow(10, lastSix);
    }

    return num;
}

// time complexity: O(1)
// space complexity: O(1)
int numWaterBottles(int numBottles, int numExchange)
{
    int total = numBottles;
    int leftover = total;

    while (numBottles)
    {
        numBottles = leftover / numExchange;
        total += numBottles;
        leftover = leftover % numExchange + numBottles;
    }

    return total;
}

int findComplement(int num)
{
    int largest = (num & (num - 1));
    largest >>= 1;
    int mask = 1;
    while (largest)
    {
        largest >>= 1;
        mask <<= 1;
        mask |= 1;
    }
    
    return ~num & mask;
}

long long fact(long long n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else 
    {
        return n * fact(n - 1);
    }
}

int numPrimeArrangements(int n)
{
    int numPrimes = 0;
    std::vector<bool> prime(n + 1, true);
    for (int p = 2; p * p <= n; p++)
    {
        // If prime[p] is not changed,
        // then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple
            // of p and are less than p^2
            // are already been marked.
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

        // Print all prime numbers
    for (int p = 2; p <= n; p++)
        if (prime[p])
            ++numPrimes;

    return fact(n) / (n * fact(n - numPrimes));
}

// time complexity: O(n)
// space complexity: O(1)
int getKth(int lo, int hi, int k)
{
    std::vector<int> cache(1001, std::numeric_limits<int>::max());

    auto compute = [](int val) {
        
        int power = 0;
        while (val != 1)
        {
            if (val % 2)
            {
                val = 3 * val + 1;
            }
            else
            {
                val /= 2;
            }
            ++power;
        }

        return power;
    };

    cache[1] = 0;

    for (size_t i = 2; i <= 1000; ++i)
    {
        cache[i] = compute(i);
    }

    std::vector<std::pair<int, int>> powers;
    for (int i = lo; i <= hi; ++i)
    {
        powers.push_back({ i, cache[i] });
    }

    std::sort(powers.begin(), powers.end(), [](std::pair<int, int>& a, std::pair<int, int>& b) {
        
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        else
        {
            return a.second < b.second;
        }
    });

    return powers[k-1].first;
}