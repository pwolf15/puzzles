# Problem Solving through Problems

## TODO: Next Permutation Variants

## Notes
* Iterative refinement of a brute-force solution.

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


## TODO

TODO: Variants
Four points in plane (p. 40)
Two rectangles intersect (p. 40)

Dutch flag (1/2/3/4) p. 46
Plus One variant p. 47
CanReachEnd variant p. 49
Delete Duplicates variants p. 51

TODO: sell buy stocks O(n log n)
TODO: sell buy stocks twice O(n^4), O(N^2)
TODO: compute an alternation, brute-force swap top and bottom, median solution

5.12 Variant: Does rand() mod n generate a number uniformly distributed in [0, n-1]?
- No, certain lower bit numbers have greater likelihood: https://stackoverflow.com/questions/10984974/why-do-people-say-there-is-modulo-bias-when-using-a-random-number-generator/10984975. For larger numbers, this could skew the stribution.

5.16 Variants p. 67

5.18 variants p. 71
5.19 Variants p.74
5.20 variant p. 75

## Strings

* how are they represented?
* comparison
* copying
* joining
* splitting
* often brute-force solutions use O(N) space, subtler solutions use string itself and reduce space complexity to O(1)
* writing from the front is slow, try the back.
* append, push_back, pop_back, insert, substr, compare
* performs well for operations from the back, worse for at middle
* comparison operators

TODO:
Rabin-Karp,
KMP,
Boyer-Moore implementations for find str

## Linked lists

* O(1) constant insertion/deletion time 
* O(n) lookup time
* List problems often have a simple brute-force solution that uses O(n) space, but a subtler solution that uses the existing list nodes to reduce space complexity.
* Very often, a problem on lists is conceptually simple, and is more about cleanly coding what's specified, rather than designing an algorithm.
* Consider using a dummy head (sometimes referred to as a sentinel) to avoid having to check for empty lists. This simplifies code, and makes bugs less likely.
* It's easy to forget to update next (and previous for double linked list) for the head and tail.
* Algorithms operating on singly linked lists often benefit from using two iterators, one ahead of the other, or one advancing quicker than the other.

### Know your linked list libraries.

* list, forward_list. list is a doubly-linked list; forward_list is singly-linked.
* push_front, emplace_front, pop_front, push_back, emplace_back, pop_back
* To transfer elements from list to another, use splice_after.
* splice, reverse, sort.
* Reverse the order of elements with reverse().
* Use sort() to sort lists.


## Stacks and Queues

* stacks: last-in, first-out semantics
* queues: first-in, first-out sematnics
* stacks: push, pop, peek
* applications for stacks: parsing
* top, push/emplace, pop
* top/pop throw exceptions with empty stack
* 

## Binary Trees

* node, ancestor, parent, child, descendant, full/perfect/complete binary trees
* left/right skews
* recursion, complexity of function call stack
* consider skewed trees when doing complexity analysis, O(log n) for balanced trees, O(n) for skewed trees
* make complexity better when given parent field
* easy to mistake parent with single child as leaf

## Heaps

* heaps are specialized binary tree: complete binary tree, where key at each node is at least a great as keys stored in its children.
* max-heap:
* log(n) insertions
* O(1) time lookup for max, 
* O(log n) for deletion of max element
* O(n) search for keyss
* also referred to as priority queue
* min-heap, symmetric version of data structure
* example problem: k longest strings in stream
* use a heap when all you care about are largest or smallest elements and do not need fast lookup, delete or search for arbitrary elements
* good for computing k largest (min-heap) or smallest (max-heap)

## Searching

* The Anatomy of a Large-Scale Hypertextual Web Search Engine
* Binary vs. general search
* Programming Pearls by Jon Bentley
* Binary search can be used for arrays, or earching intervals of real numbers or integers.
* If solution with computation after sorting is faster than sorting, look into incomplete sort
* Time/space tradeoffs, multiple passes through data
* C++ search libraries: binary_search, lower_bound, upper_bound

## Hash-maps

* O(1) inserts, deletes, and lookups
* average of lookups, inserts, and deletions O(1 + n/m) time complexity, where n is number of objects and is length of array
* soft requirement for spread keys (hash codes for a subset of objects should be uniformly distributed across the underlying array)


### TODO.

Implement variants
Implement test for cyclicity using hash map (7.3)

## Recursion

* An approach to problem solving where the solution partially depends on solutins to smaller instances of related problems.
* Common use-cases: input expressed as recursive rules e.g recursive grammar, searching, enumeration, divide-and-conquer, and decomposition. 
* Two ingredients to solving recursion
1. Identifying base csaes.
2. Ensuring progress
* Divide-and-conquer: decompose a problem into two or more smaller independent subproblems of the same kind, ntil it gets to instances that are simple enough to be solved directly. E.g. mergesort, quicksort.
* Divide-and-conquer are subset of recursion. Also included are problems with single sub-problem (binary search), non-independent sub-problems (dynamic programming), and sub-problems of different type (regex expresison matching). Sometimes, iterative solutions are used instead of recursion to reduce space complexity and improve runtime.
* Recursion is especially suitable when the input is expressed using recursive rules. such as computer grammar.
* Recursion is a good choice for search, enumeration, and divide-and-conquer.
* Use recursion as an alternative to deeply nested iteration loops. For example, recursion is much better when you have an undefined number of levels, such as the IP address problem generalized to k substrings.
* If you are asked to remove recursion from a problem, consider mimicking the call stack with a stack data structure.
* Recursion can be easily removed from a tail-recursive program by using a while-loop -- no stack is needed. (Optimizing compilers do this.)
* If a recursive function may end up being called with the same arguments more than once, ache the results -- this is the idea behind Dynamic Programming.

### Current 7.8, 15.1, 16.1

#

``` sml
- use "linked_lists.ml";
[opening linked_lists.ml]
datatype 'a linkedlist = Cons of 'a * 'a linkedlist | Empty
val it = () : unit
```