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

## merge sort
- basic plan
  - divide array into two halves 
  - recursively sort each other
  - merge two halves
- proposition
  - time: $\Theta(N \log{N})$
    - compares $C(N) \in [\frac{1}{2} N \log{N}, N \log{N}]$, also insensitive to input
    - access $A(N) = 6N \log{N}$, $2N$ for copy, $2N$ for move back, $2N$ for compares
  - auxiliary space: $\Theta(N)$
- merge sort is optimal with respect to compares but not to memory
- any compare-based algorithm has lower bound $\Theta(N \log{N} )$
- lower bound may not hold when knowing more information about initial order, distribution or representation of keys

## quick sort

- basic plan
  - shuffle the array (guarantee performance)
  - partition so that, for some j
    - entry `a[j]` is in place
    - no larger entry to the left of `a[j]`
    - no smaller entry to the right of `a[j]`
  - sort each piece recursively

![image-20231009233608066](/home/guo/mypro/alg/alg/assets/image-20231009233608066.png)

- proposition
  - best case: compares $C_N \sim N \log{N}$
  - worst case: compares $C_N \sim \frac{1}{2}N^2$
  - average case:
    - for distinct keys, compares $C_n \sim 2N \log{N}$, exchanges $E_N \sim \frac{1}{3} N \log{N}$
  - in-place
  - not stable
- practical improvements
  - insertion sort small sub-arrays
  - median of sample (median of `arr[low]`, `arr[mid]` and `arr[high]`)
  - entropy-optimal sorting: sub-arrays of equal keys often occur. from linearithmic to linear (see below)
- three-way partion (much faster with large number of duplicate keys)

![image-20231009233906376](/home/guo/mypro/alg/alg/assets/image-20231009233906376.png)



# reference
1. [princeton algorithm, 4th edition](https://algs4.cs.princeton.edu/home/)
2. [latex mathematical sysmbols](https://www.cmor-faculty.rice.edu/~heinken/latex/symbols.pdf)
3. [counting sort](https://www.geeksforgeeks.org/counting-sort/)
4. [shell sort](https://www.geeksforgeeks.org/shellsort/)
