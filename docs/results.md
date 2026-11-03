# Chapter 3: Performance Analysis

Let:

N = Number of page references

F = Number of memory frames

## 3.1 FIFO Complexity

The implementation searches the frames to check
whether a page exists.

Time Complexity: O(N * F)

Auxiliary Space Complexity: O(1)

## 3.2 LRU Complexity

The implementation searches frames and tracks
the latest access position of each frame.

Time Complexity: O(N * F)

Auxiliary Space Complexity: O(F)

## 3.3 Optimal Complexity

For every page fault with full memory, the
implementation searches future references for
each page currently stored in memory.

Worst-case Time Complexity: O(N^2 * F)

Auxiliary Space Complexity: O(1)

## 3.4 Memory Usage

The simulator uses:

- O(N) memory for the reference string.
- O(F) memory for the frames.
- O(F) auxiliary memory for LRU timestamps.

Total Space Complexity: O(N + F).

## 3.5 Performance Comparison

The number of Page Faults depends on:

- The reference string.
- The number of frames.
- The replacement algorithm.

Optimal provides the minimum possible number
of page faults for a known reference string.

FIFO and LRU may produce different results.
