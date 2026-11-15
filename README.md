# DataStructuresAndAlgo Repository

Welcome to the **DataStructuresAndAlgo** repository! This comprehensive collection of Data Structures and Algorithms (DSA) questions aims to provide a solid foundation for your coding and problem-solving skills. This repository focuses on questions from GeeksforGeeks and LeetCode, particularly drawing from the course "Complete Interview Preparation" by GFG.

## Repository Structure

```
DataStructuresAndAlgo/
├── Competitive Programming/              # Codeforces, grouped by technique
│   ├── Binary Search/
│   ├── Bit Manipulation/
│   ├── Brute Force/
│   ├── Constructive/
│   ├── Games/
│   ├── Greedy/
│   ├── Implementation/
│   ├── Math/
│   ├── Prefix Sums/
│   └── Strings/
├── Contests Upsolving Leetcode and GFG/  # LeetCode/GFG, grouped by topic
│   ├── Arrays/                           # Hashing and Prefix Sum, Matrix
│   ├── Bit Manipulation/                 # Bit Tricks, Bitwise Subarrays, XOR
│   ├── Dynamic Programming/              # 6 pattern subfolders (see below)
│   ├── Fenwick and Segment Trees/
│   ├── Graph/                            # DFS and BFS, Disjoint Sets, Shortest Path, Topo
│   ├── Math/                             # Combinatorics, Geometry, Number Theory
│   ├── Recursion and Backtracking/
│   ├── Searching and Sorting/            # Binary Search, Greedy, Heaps and Priority Queues, Two Pointers
│   ├── Stacks/                           # + Monotonic Stack
│   ├── Strings/                          # Binary Strings, Counting, Matching, Simulation, Trie
│   └── Trees/
├── SHEETs/                               # consolidated topic-wise sheet notes
├── OOPS/                                 # OOP theory + design implementations
├── Standard-template-library/            # STL reference notes
├── container_printer.hpp                 # reusable debug printer
└── README.md
```

### 1. `Competitive Programming/`

Codeforces problems grouped by the technique needed to solve them. Each file contains the problem statement/observations and, where useful, more than one approach.

### 2. `Contests Upsolving Leetcode and GFG/`

Medium-to-hard problems from LeetCode weekly/biweekly contests and GFG contests, grouped by data structure or topic. Each topic is split into pattern-specific subfolders carrying at least three problems:

| Topic | Subfolders |
|---|---|
| `Arrays` | Hashing and Prefix Sum, Matrix |
| `Bit Manipulation` | Bit Tricks, Bitwise Subarrays, XOR |
| `Dynamic Programming` | Take or Not Take DP, Partition DP, Non-Standard DP, Bitwise DP, LIS Variations, DP on Trees |
| `Graph` | DFS and BFS, Disjoint Sets, Shortest Path, Topological Sorting |
| `Math` | Combinatorics, Geometry, Number Theory |
| `Searching and Sorting` | Binary Search, Greedy, Heaps and Priority Queues, Two Pointers |
| `Stacks` | Monotonic Stack |
| `Strings` | Binary Strings, String Counting, String Matching, String Simulation, Trie |

`Fenwick and Segment Trees`, `Recursion and Backtracking`, and `Trees` are small enough to stay flat. `Trees` holds tree-structure problems (LCA, path counting) plus the binary-lifting concept note, while tree DP lives under `Dynamic Programming/DP on Trees`. `Stacks` keeps two plain stack problems (`Clumsy factorial`, `Remove the balls`) at its root and groups the rest under `Monotonic Stack`. `Two Pointers` also covers the sliding-window problems.

Files are named after the contest problem they solve and are never renamed during reorganisation — moves use `git mv`, so history follows the file.

### 3. `SHEETs/`

Consolidated topic-wise notes and solutions for standard sheets such as Love Babbar 450 and Striver A2Z. Each file covers one topic, with problems arranged sequentially.

### 4. `OOPS/`

C++ OOP theory plus design-oriented implementations (Bank, Library Management, Stock Broker).

### 5. `Standard-template-library/`

STL reference notes and examples.

The scratch folders `CP/`, `excalidraw/`, and `test/` are local-only and git-ignored.

## Language

All the programs and solutions in this repository have been crafted exclusively in C++. The use of C++ allows you to explore DSA concepts in a versatile and efficient programming language, and it aligns with the primary focus of the repository.
