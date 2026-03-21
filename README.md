<div align="center">
  <a href="https://github.com/Lloyalcole/CMSC123-FinalProject-GroupA">
     <img src="banner.png" alt="banner" width="400"/>
  </div>

  <h1>Mini Library of Data Structures in C++</h1>
  <p>A small, open-source collection of data structure implementations written in C++ built for CMSC 123 as a final project.</p>

  [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
</div>

---
 
## Table of Contents
 
- [About](#about)
- [Data Structures](#data-structures)
- [Core Concepts](#core-concepts)
- [Getting Started](#getting-started)
- [Running Tests](#running-tests)
- [Benchmarks](#benchmarks)
- [Directory Structure](#directory-structure)
- [Contributing](#contributing)
- [Authors](#authors)
- [License](#license)
 
---
 
## About
 
This is a hand-rolled C++ data structures library implementing common Abstract Data Types (ADTs) from scratch. No STL containers were used in the core implementations — just raw arrays, pointers, linked nodes, and a bit of randomness.
 
The goal was to deeply understand how these structures work under the hood, and to present them in a way that is readable, testable, and actually fun to look at.
 
**Implemented ADTs:**
 
- Stack (Array Stack)
- Queue (Singly Linked List)
- Deque (Array Deque)
- List (Array Deque + Doubly Linked List)
- Priority Queue (Meldable Heap)
- Sorted Set (Skiplist + Red-Black Tree)
- Unsorted Set (Chained Hash Table)
- Graph (Adjacency Matrix)
 
---
 
## Data Structures
 
| Structure | Implementation | File |
|---|---|---|
| Stack | Array Stack | `src/arraystack.h` |
| Queue | Singly Linked List | `src/sllist.h` |
| Deque / List | Array Deque | `src/arraydeque.h` |
| List | Doubly Linked List | `src/dllist.h` |
| Priority Queue | Meldable Heap | `src/meldableheap.h` |
| Sorted Set | Skiplist | `src/skiplist.h` |
| Sorted Set | Red-Black Tree | `src/redblacktrees.h` |
| Unsorted Set | Chained Hash Table | `src/chainedhashtable.h` |
| Graph | Adjacency Matrix | `src/adjacencymatrix.h` |
 
---
 
## Core Concepts
 
### Why build this from scratch?
 
Understanding a data structure means being able to implement it, not just use it. This library exists as proof of that understanding. Every structure here was written by hand — no copying from the textbook, no wrapping STL.
 
### What makes this different from the textbook?
 
**ArrayDeque**
- Uses a **1.5x growth factor** (`capacity + capacity / 2`) instead of the textbook's 2x, reducing wasted memory while keeping amortized O(1) operations.
- **Shrinks** when the array is 25% full (`count <= capacity / 4`), halving the buffer. The textbook version only ever grows.
- Added `peekFirst()` and `peekLast()` — the textbook's ArrayDeque only implements the List interface; ours also implements Deque.
- Added `operator[]` for natural index access.
 
**MeldableHeap**
- Implements `absorb(other)` — merges an entire second heap into this one in O(log n) expected time, emptying the other heap in the process.
- Implements `remove(Node* u)` — removes a specific node (not just the root) by merging its children and relinking.
- Implements `peek()` — inspect the minimum without removing it.
- Proper destructor with recursive `deleteTree()` to avoid memory leaks.
 
**ArrayStack**
- Starts with capacity 0 and only allocates on first push — no wasted memory for empty stacks.
- Doubles capacity on resize, with a special case for capacity 0 → 1.
- Proper destructor, `clear()` resets without deallocating.
 
**SLListQueue**
- Tracks both `head` and `tail` pointers for true O(1) enqueue and dequeue.
- `clear()` walks the list and deletes all nodes cleanly.
- Includes `front()` for peeking without removal.
 
**DLList**
- Uses a **sentinel dummy node** whose `next` and `prev` always point to the first and last real nodes — eliminates all null-pointer edge cases for insert and remove.
- `getNode(i)` traverses from whichever end is closer (`i < count/2` → from front, else from back), giving O(min(i, n-i)) traversal.
- `addBefore(w, x)` and `removeNode(w)` are private helpers that keep the public interface clean.
 
**SkipList**
- Randomized level assignment on insert — each new node flips a coin per level, up to `maxLevel = 16`.
- Uses a sentinel `head` node at max level to simplify traversal logic.
- Expected O(log n) for `add`, `remove`, and `contains`.
 
**RedBlackTree**
- Implemented as a **Graph** (extends the `Graph` interface) — tree edges are treated as directed graph edges.
- Tracks nodes in a `std::vector` so they can be referenced by index for graph operations like `hasEdge(u, v)` and `neighbours(u)`.
- `fixViolation()` handles all four rebalancing cases (recolor, left rotation, right rotation, left-right / right-left combos).
- `inDegree` of root is 0; all other nodes have inDegree 1.
 
**ChainedHashTable**
- Uses `std::vector<std::list<T>>` — a vector of linked list buckets.
- Default capacity of 101 (a prime, which distributes keys more evenly).
- `add()` checks for duplicates via `contains()` before inserting.
- `getHash()` uses `abs(x) % capacity` — simple and effective for integer keys.
 
**AdjacencyMatrix**
- Supports both **directed** and **undirected** graphs via a constructor flag.
- Uses `NaN` (not a number) as the sentinel for absent edges — avoids ambiguity with zero-weight edges.
- `addVertex()` dynamically grows the matrix by adding a new row and column.
- `removeVertex(v)` correctly adjusts `edge_count_` for both directions before erasing.
- `forEachEdge()` accepts a lambda/callback for flexible edge traversal.
 
---
 
## Time Complexities
 
### ArrayDeque
 
| Operation | Time Complexity |
|---|---|
| `get(i)` / `set(i, x)` | O(1) |
| `addFirst(x)` / `addLast(x)` | O(1) amortized |
| `removeFirst()` / `removeLast()` | O(1) amortized |
| `add(i, x)` / `remove(i)` | O(1 + min(i, n−i)) |
 
### MeldableHeap
 
| Operation | Time Complexity |
|---|---|
| `add(x)` | O(log n) expected |
| `remove()` | O(log n) expected |
| `remove(Node* u)` | O(log n) expected |
| `absorb(other)` | O(log n) expected |
| `peek()` | O(1) |
| `merge(h1, h2)` | O(log n) expected |
 
### ArrayStack
 
| Operation | Time Complexity |
|---|---|
| `push(x)` | O(1) amortized |
| `pop()` | O(1) |
| `peek()` | O(1) |
 
### SLListQueue
 
| Operation | Time Complexity |
|---|---|
| `enqueue(x)` | O(1) |
| `dequeue()` | O(1) |
| `front()` | O(1) |
 
### DLList
 
| Operation | Time Complexity |
|---|---|
| `get(i)` / `set(i, x)` | O(1 + min(i, n−i)) |
| `add(i, x)` / `remove(i)` | O(1 + min(i, n−i)) |
 
### SkipList
 
| Operation | Time Complexity |
|---|---|
| `add(x)` | O(log n) expected |
| `remove(x)` | O(log n) expected |
| `contains(x)` | O(log n) expected |
 
### RedBlackTree
 
| Operation | Time Complexity |
|---|---|
| `insertValue(x)` | O(log n) |
| `hasEdge(u, v)` | O(1) |
| `neighbours(u)` | O(1) |
 
### ChainedHashTable
 
| Operation | Time Complexity |
|---|---|
| `add(x)` | O(1) expected |
| `remove(x)` | O(1) expected |
| `contains(x)` | O(1) expected |
 
### AdjacencyMatrix
 
| Operation | Time Complexity |
|---|---|
| `hasEdge(u, v)` | O(1) |
| `addEdge(u, v)` | O(1) |
| `removeEdge(u, v)` | O(1) |
| `addVertex()` | O(n) |
| `removeVertex(v)` | O(n²) |
| `neighbours(u)` | O(n) |
| `inDegree(v)` / `outDegree(v)` | O(n) |
 
---
 
## Getting Started
 
### Prerequisites
 
- A C++ compiler with C++11 support or later (g++, clang++)
- Make (optional, for using the Makefile)
 
### Clone the repo
 
```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
```
 
### Compile a test manually
 
```bash
g++ -std=c++11 tests/arraydeque.cpp -o arraydeque_test
./arraydeque_test
```
 
### Using Make
 
```bash
make arraydeque
make meldableheap
make all
```
 
---
 
## Running Tests
 
Each data structure has its own test file under `tests/`. Tests come in two styles:

<div align="center">
  <img src="dsameme.gif" alt="dsameme"/>
</div>
 
**Narrative tests** — operations play out as a story, output is automatic:
 
```bash
# ArrayDeque — Sir Eli checks the repo
g++ -std=c++11 tests/arraydeque.cpp -o test && ./test
 
# MeldableHeap — Sir Eli grades the class
g++ -std=c++11 tests/meldableheap.cpp -o test && ./test
```
 
**Interactive menu tests** — you enter values and choose operations manually:
 
```bash
# DLList
g++ -std=c++11 tests/dllist.cpp -o test && ./test
 
# ArrayStack
g++ -std=c++11 tests/arraystack.cpp -o test && ./test
 
# SLListQueue
g++ -std=c++11 tests/sllist.cpp -o test && ./test
 
# ChainedHashTable
g++ -std=c++11 tests/chainedhashtable.cpp -o test && ./test
 
# SkipList
g++ -std=c++11 tests/skiplist.cpp -o test && ./test
 
# RedBlackTree
g++ -std=c++11 tests/redblacktrees.cpp -o test && ./test
 
# AdjacencyMatrix
g++ -std=c++11 tests/adjacencymatrix.cpp -o test && ./test
```
 
### What each test covers
 
| Test File | Style | Operations Tested |
|---|---|---|
| `arraydeque.cpp` | Narrative | addFirst, addLast, add, peekFirst, peekLast, get, set, removeFirst, removeLast, remove, size, isEmpty, clear, exceptions |
| `meldableheap.cpp` | Narrative | add, peek, remove, absorb, isEmpty, size, exceptions |
| `dllist.cpp` | Interactive | add at index, add to tail, remove, get, set, size, print |
| `arraystack.cpp` | Interactive | push, pop, peek, size, isEmpty, clear |
| `sllist.cpp` | Interactive | enqueue, dequeue, front, size, isEmpty, clear, print |
| `chainedhashtable.cpp` | Interactive | add, remove, contains |
| `skiplist.cpp` | Interactive | add, remove, contains |
| `redblacktrees.cpp` | Interactive | insertValue, neighbours, hasEdge, edgeWeight |
| `adjacencymatrix.cpp` | Interactive | addEdge, removeEdge, addVertex, removeVertex, display matrix |
 
---
 
## Benchmarks
 
Benchmarks measure the time taken for large-scale operations on each data structure. Results are in milliseconds. To run benchmarks yourself:
 
```bash
g++ -std=c++11 -O2 benchmarks/benchmark.cpp -o bench && ./bench
```
 
| Structure | Operation | Count | Time (ms) |
|---|---|---|---|
| ArrayStack | Push + Pop | 100,000 | 4.1793 |
| ArrayDeque | AddLast + RemoveFirst | 100,000 | 5.7922 |
| SLListQueue | Enqueue + Dequeue | 100,000 | 11.6899 |
| ChainedHashTable | Insert | 100,000 | 145.6715 |
| DLList | Head Add + Head Remove | 10,000 | 1.1600 |
| SkipList | Insert | 10,000 | 11.1054 |
| MeldableHeap | Add + Remove | 10,000 | 13.2600 |
| RedBlackTree | Balanced Insert | 10,000 | 3.4716 |
| AdjacencyMatrix | AddEdge | 1,000 | 0.0792 |
 
> Benchmarks will be updated once all implementations are finalized.
 
---
 
## Directory Structure
 
```
benchmarks/
  centralbenchmark.cpp
include/
  deque.h
  graph.h
  list.h
  priorityqueue.h
  queue.h
  sset.h
  stack.h
  uset.h
src/
  adjacencymatrix.h
  arraydeque.h
  arraystack.h
  chainedhashtable.h
  dllist.h
  meldableheap.h
  redblacktrees.h
  skiplist.h
  sllist.h
tests/
  adjacencymatrix.cpp
  arraydeque.cpp
  arraystack.cpp
  chainedhashtable.cpp
  dllist.cpp
  meldableheap.cpp
  redblacktrees.cpp
  skiplist.cpp
  sllist.cpp
LICENSE
README.md
banner.png
dsameme.gif
```
 
---
 
## Contributing
 
This is a class project, but contributions are welcome after submission.
 
- Fork the repo
- Create a branch (`git checkout -b feature/your-feature`)
- Commit your changes
- Open a pull request
 
Please keep code style consistent with existing files — templated classes, `using namespace std` where applicable, and narrative-style test files.
 
---

## Authors

- **Hannah** — [@hxnie0](https://github.com/hxnie0)
- **Cole** — [@Lloyalcole](https://github.com/Lloyalcole)
- **Nino** — [@Geeyannn](https://github.com/Geeyannn)
- **Drebin** — [@Leftakoyaki](https://github.com/Leftakoyaki)

Built for CMSC 123 requirement under Sir Eli Adrian Tan.

---
 
## Acknowledgements
 
- **Sir Eli Tan** — for the guidance during the whole duration of the course and the generous deadlines
- **Pat Morin** — [Open Data Structures (C++ Edition)](https://opendatastructures.org/) — the primary reference for all implementations in this library
- **Open Source Initiative** — for the [Open Source Definition](https://opensource.org/osd) that this project is licensed under
- **GitHub** — for the [open source licensing guide](https://github.com/readme/guides/open-source-licensing) that helped us pick GPL v3
- **Zalando** — for the [README template](https://github.com/zalando/zalando-howto-open-source/blob/master/READMEtemplate.md#readme) that structured this document
- **dec0dOS** — for the [Amazing GitHub Template](https://github.com/dec0dOS/amazing-github-template#readme) used as additional reference
- **ma-shamshiri** — for the [Pacman Game README](https://github.com/ma-shamshiri/Pacman-Game#readme) as a formatting inspiration
 
### References
 
- [1] https://opensource.org/osd
- [2] https://github.com/readme/guides/open-source-licensing
- [3] https://opendatastructures.org/ods-cpp/10_Heaps.html
- [4] https://opendatastructures.org/ods-cpp/12_Graphs.html
- [5] https://github.com/zalando/zalando-howto-open-source/blob/master/READMEtemplate.md#readme
- [6] https://github.com/dec0dOS/amazing-github-template#readme
- [7] https://github.com/ma-shamshiri/Pacman-Game#readme
 
---

## License

This project is licensed under the **GNU General Public License v3.0**. See [LICENSE](LICENSE) for details.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

**Permissions:** Commercial use, Modification, Distribution, Patent use, Private use

**Conditions:** License and copyright notice must be preserved, State changes must be documented, Source code must be disclosed, Derivative works must use the same license

**Limitations:** No liability, No warranty
