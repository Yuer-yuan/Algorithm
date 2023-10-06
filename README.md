[TOC]
# sort
## elementary sorts
### selection sort
at each turn, select the right element from rest, and put it in final position.
- proposition
  - compares: $\sum_{0}^{N-1}(N-i-1) = \frac{N(N-1)}{2} \sim \frac{N^2}{2} = \Theta (N^2)$
  - exchanges: $N = \Theta (N)$
- running time insensitive to input: quadratic time, even if input is sorted
- data movement is minimal: linear time of exchanges

### insertion sort
at each turn, select right element from "seen" elements, then move it from right to left, switching each "larger" element to its left
- proposition
  - best case: $N-1$ compares, $0$ exchanges
  - worst case: $\sim \frac{N^2}{2}$ compares, $\sim \frac{N^2}{2}$ exchanges
  - average case: with random input, assume that each item goes half way. $\sim \frac{N^2}{4}$ compares, $\sim \frac{N^2}{4}$ exchanges
- exchanges equal to inversions
- excellent for partially sorted arrays whose inversions is $O(N)$ -- in linear time, for compares = exchanges + $N - 1$
- fine to tiny arrays

### shell sort
shell sort is an extension of insertion sort. partially sorted array is friendly to insertion sort.

- `h-sorted` array: subarray that has strike h started anywhere is sorted

- `h-sort` procedure doesn't spoil `g-sorted` array

- Q: what kind of incremental sequence should we use?
 - powers of two: 1, 2, 4, ... -- not good
 - powers of two minus one: 1, 3, 7, ... -- maybe
 - $3x + 1$: 1, 4, 13, ... -- ok and easy to compute
 - `Sedgewick`: 1, 5, 18, 41, 109, 209: 
 $$
 \forall i \geq 0, s[i] = \left \{ \begin{array}{rcl}
9 \times (4^j - 2^j) + 1 & where & j = \lfloor \frac{i}{2} \rfloor & and & i = 2k \\
4^j - 3 \times 2^j + 1 & where & j = 2 + \lfloor \frac{i}{2} \rfloor & and & i = 2k + 1 \\
 \end{array} \right. \\
 $$

- proposition: 
  - worst case: $N ^ {\frac{3}{2}}$ (using $3x + 1$) compares

# reference
1. [princeton algorithm, 4th edition](https://algs4.cs.princeton.edu/home/)
2. [latex mathematical sysmbols](https://www.cmor-faculty.rice.edu/~heinken/latex/symbols.pdf)

