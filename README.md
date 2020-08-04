# Problem Solving through Problems

## Large-Scale System Design

* https://github.com/donnemartin/system-design-primer
* Juval Lowy
* John Lakos
* Data-intensive applications

## Primitives

### Key strategies

* Bitwise operators: &, |, >>, <<, ~, ^
* std::numeric_limits e.g. numeric_limits<int>::min(), numeric_limits<double>::infinity()
* Comparison of floating points: use a threshold
* cmath: abs, fabs, ceil, floor, min, max, pow, log, sqrt
* converting between integers, characters, and strings: 
    * char to int: x - '0' 
    * int to string: to_string(123)
    * string to int: stoi("42")
* random: uniform_int_distribution, uniform_real_distribution, generate_canonical
* swap: exchange values succinctly

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Add Digits/Digital Root](include/Primitives.hpp#L9)                                      | LC  #258              |
| [Rectangle Intersection](Primitives/RectangleIntersection/RectangleIntersection.cpp#L64)  | EPI p. 39             |
| [Uniform Random Distribution](Primitives/UniformRandom/UniformRandom.cpp#L37)             | EPI p. 38             | 
| [Hamming Weight/Count Bits](Primitives/Primitives.hpp#L15)                                | EPI p. 25 / LC #191   |
| [Is Power Of Three](include/Primitives.hpp#L17)                                           | LC #326               |
| [Missing Number](include/Primitives.hpp#L19)                                              | LC #268               |
| [Count Primes](include/Primitives.hpp#L21)                                                | LC #204               |


## Arrays

### Key strategies

* Array problems often have brute-force solutions that use O(n) space, but there are subtler solutions that use the array itself
to reduce space complexity to O(1)
* Filling an array from the front is slow, so see if it's possible to write values from the back.
* Instead of deleting an entry which requires moving all entries to the left, consider overwriting it.
* When dealing with integers encoded by an array, consider processing digits from the the back of the array. Alternatively, reverse the array
so the least-significant digit is the first entry.
* Be comfortable with writing code that operates on subarrays.
* It's incredibly easy to make off-by-1 errors when operating on arrays -- reading past the last element of an array is a common error which has
catastrophic consequences.
* Don't worry about preserving the integrity of the array (sortedness, keeping equal entries together, etc.) until it is time to return.
* An array is a good data structure when you know the distribution of elements in advance. For example, a Boolean array of length W is a good choice for representing a subset of {0, 1, ..., W-1}. (When using a Boolean array to represent a subset of {1, 2, 3,...,n}, allocate an array of size[n + 1]) to simplify indexing.)
* When operating on 2D arrays, use parallel logic for rows and columns.
* Somtimes its easier to simulate the specification, than to analytically solve for the result. Fo rexample, rather than writing a formulat for the i-th entry in the spiral order for an nxn matrix, just compute the output from the beginning.
* Know vector is dynamically-sized, array is fixed-size.
* KNow allocation and instantiation syntax. 
* Know how to construct a subarray from an array
* Know how to create a 2D array
* Know push_back, emplace_back
* Understand how copy works (deep vs. shallow). Know which is implemented in the vector class.
* Key methods: lower_bound, upper_bound, binary_search, fill, min_element, max_element, reverse, rotate, sort
* Understand the variants of these methods.

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Remove Duplicates from Sorted Array](include/Arrays.hpp#L12)                             | LC #83                |
| [Rotate](include/Arrays.hpp#L15)                                                          | LC #189               |
| [Rotate Image](include/Arrays.hpp#L19)                                                    | LC #48                |
| [EvenOdd](include/Arrays.hpp#L21)                                                         | EPI 5.0               |
| [DutchFlagPartition](include/Arrays.hpp#L25)                                              | EPI 5.1               |

### Key strategies

* Remove Duplicates (sorted)

## Strings

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [First Unique Char](include/Strings.hpp#L8)                                               | LC #387               |

## Linked Lists

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Reverse](include/LinkedLists.hpp#L13)                                                    | LC #206               |

## Design

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [ShuffledArray](include/Design.hpp#L6)                                                    | LC #384               |
| [HashSet](include/Design.hpp#L21)                                                         | LC #705               |

## Dynamic Programming

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Climb Stairs](include/DynamicProgramming.hpp#L7)                                         | LC #70                |

## Linked Lists

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Reverse List](include/LinkedLists.hpp#L13)                                               | LC #206               |
| [Is Palindrome](include/LinkedLists.hpp#L15)                                              | LC #234               |

## Strings

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [First Unique Char](include/Strings.hpp#L8)                                               | LC #387               |
| [Is Anagram](include/Strings.hpp#L11)                                                     | LC #242               |
| [Detect Captial Use](include/Strings.hpp#L13)                                             | LC #520                |

## Trees

| Problems                                                                                  | Source                | 
| ----------------------------------------------------------------------------------------- | --------------------- |
| [Sorted Array to BST](include/DynamicProgramming.hpp#L13)                                 | LC #108               |


TODO: Variants
Four points in plane (p. 40)
Two rectangles intersect (p. 40)

Dutch flag (1/2/3/4) p. 46
Plus One variant p. 47
CanReachEnd variant p. 49
Delete Duplicates variants p. 51