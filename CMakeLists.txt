cmake_minimum_required(VERSION 3.10)

project (LeetCode)

# Common
# add_subdirectory(Common)

# set(CMAKE_CXX_CLANG_TIDY
#     clang-tidy;
#     -header-filter=.;
#     -checks=*;)

add_subdirectory(MaxSubArray)
add_subdirectory(LengthOfLastWord)
add_subdirectory(PlusOne)
add_subdirectory(Sqrt)
add_subdirectory(ClimbingStairs)
add_subdirectory(MergeSortedArrays)
#add_subdirectory(SameTree)
#add_subdirectory(SymmetricTree)
#add_subdirectory(MaxTreeDepth)
add_subdirectory(PascalsTriangle)
add_subdirectory(BestTimeBuySellStocks)
# add_subdirectory(Trees)
add_subdirectory(SingleNumber)
add_subdirectory(LinkedLists)
add_subdirectory(TwoCityScheduling)
add_subdirectory(RandomPickWithWeight)
add_subdirectory(QueueReconstruction)
add_subdirectory(CoinChange)
add_subdirectory(CutRods)
add_subdirectory(PowerOfTwo)
add_subdirectory(IsSubsequence)
add_subdirectory(SearchInsert)
add_subdirectory(SortColors)
add_subdirectory(RandomizedSet)
add_subdirectory(LargestDivisibleSubset)
add_subdirectory(ValidateIP)
add_subdirectory(SurroundedRegions)
add_subdirectory(PermutationSequence)
add_subdirectory(SingleNumberII)
add_subdirectory(FindDuplicate)
add_subdirectory(PerfectSquares)
add_subdirectory(HIndex)
add_subdirectory(FindItinerary)
add_subdirectory(Primitives)
add_subdirectory(UniquePaths)
add_subdirectory(DataStructures)
add_subdirectory(Recursion)
add_subdirectory(Arrays)
add_subdirectory(Numbers)
add_subdirectory(Strings)
add_subdirectory(ProjectEuler)
add_subdirectory(Math)

# Monthly Challenges
add_subdirectory(MonthlyChallenge)


include_directories(include)
add_compile_options(--std=c++2a)

# grouped solutions
add_library(Arrays              src/Arrays.cpp)
add_library(Primitives          src/Primitives.cpp)
add_library(Strings             src/Strings.cpp)
add_library(LinkedLists         src/LinkedLists.cpp)
add_library(DynamicProgramming  src/DynamicProgramming.cpp)
add_library(Design              src/Design.cpp)
add_library(Trees               src/Trees.cpp)
add_library(Recursion           src/Recursion.cpp)
add_library(Stacks              src/Stacks.cpp)
add_library(Queues              src/Queues.cpp)
add_library(Heaps               src/Heaps.cpp)
add_library(Search              src/Search.cpp)
add_library(HashMaps            src/HashMaps.cpp)

add_subdirectory(test)