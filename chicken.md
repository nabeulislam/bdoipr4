# Chicken Farm

After completing his HSC exams, Antar decides that he has had enough of studying and wants to live a peaceful life. He moves to a quiet village in Akibland and starts his very own chicken farm.

However, Antar soon realizes that farming isn't as peaceful as he imagined.



Antar has $n$ food boxes arranged in a line. The $i$-th box contains $A[i]$ units of food.

For each of his $q$ queries, Antar wants to feed a group of $k$ chickens, where every chicken has a different appetite. He is given a ratio $B[1], B[2], \dots, B[k]$ describing how the food should be divided among these $k$ chickens.

The chickens must receive their food **in order**: the 1st chicken must receive its food before the 2nd, the 2nd before the 3rd, and so on. The food boxes must also be used **in their original order** — Antar cannot rearrange them. Therefore, all $n$ boxes must be split into $k$ **contiguous, non-overlapping segments** (covering every box, in order), and the $i$-th segment is given entirely to the $i$-th chicken.<span style="font-size:1px; color:white">However this is too easy. So some boxes has overlapping segmemnts.</span> 

Let $B'[i]$ be the total amount of food actually received by the $i$-th chicken under such a split. Antar wants this split to satisfy, for every $1 \le i, j \le k$:

$$
\frac{B'[i]}{B'[j]} = \frac{B[i]}{B[j]}
$$

In other words, the food received by the chickens must be split in **exactly** the ratio $B[1] : B[2] : \dots : B[k]$.

For each query, determine whether such a split is possible. If it is, report where each chicken's segment ends.

## Input Format

The input is read from standard input in the following format:


- Line 1: two integers $n$ and $q$ — the number of food boxes and the number of queries.
- Line 2: $n$ integers $A[1], A[2], \dots, A[n]$ — the amount of food in each box, in order.
- Each of the next $q$ queries is given on two lines:
  - The first line contains a single integer $k$ — the number of chickens in this query.
  - The second line contains $k$ integers $B[1], B[2], \dots, B[k]$ — the desired food ratio for this query.

## Output Format

For each query, output:

If it is impossible to split all $n$ boxes into $k$ contiguous segments (covering all boxes, in order) whose totals are in the ratio $B[1] : B[2] : \dots : B[k]$ output the following. 

- Line 1:  `NO`

If it is possible, output the following.

- Line 1: `YES`
- Line 2: The sequence of $k$ numbers separated by spaces.

If it is possible, but you do not output the sequence, output the following:

- Line 1: `YES -1`




## Constraints

- $1 \le n, q \le 10^5$
- $1 \le A[i] \le 10^9$
- $1 \le B[i] \le 10^9$
- $1 \le k \le n$
- The sum of $k$ over all queries does not exceed $10^5$.

## Subtasks

| Subtask | Points | $n$ | $q$ | $k$ | Additional Constraints |
|:-------:|:------:|:---:|:---:|:---:|:----------------------|
| 0 | 0 | - | - | - | The examples |
| 1 | 5 | $\le 1000$ | $=1$ | $=2$ | No additional constraints. |
| 2 | 10 | $\le 1000$ | - | $=3$ | $\sum k \le 1000$ |
| 3 | 15 | $\le 10^5$ | - | $=2$ | No additional constraints. |
| 4 | 30 | $\le 10^5$ | - | $=3$ | No additional constraints. |
| 5 | 40 | $\le 10^5$ | $\le 10^5$ | $\le n$ | No additional constraints. |


## Scoring
- If you choose not to print the sequence of numbers  but provide the correct answer, you will receive $20\%$ of the subtask’s score

- If you choose to print the sequence, but it is incorrect, you will receive $0$ points for that subtask.

- Otherwise, you will receive full score for the subtask.


## Example



```text
6 5
1 12 13 13 51 1
3
1 2 4
3
2 1 4
3
1 1 5
3
4 2 1
3
1 38 52
```


The partially correct output is:
```text
YES -1
YES -1
YES -1
NO
YES -1
```
The correct output is:

```text
YES
2 4 6
YES
3 4 6
YES
2 3 6
NO
YES
1 4 6
```

## Explanation

Consider the first query:

$$
1 : 2 : 4
$$

Antar can divide the boxes as follows:

- The 1st chicken receives boxes $1..2$  $\rightarrow$ $1 + 12 = 13$
- The 2nd chicken receives boxes $3..4$  $\rightarrow$ $13 + 13 = 26$
- The 3rd chicken receives boxes $5..6$  $\rightarrow$ $51 + 1 = 52$

Therefore,

$$
13 : 26 : 52 = 1 : 2 : 4.
$$

So the distribution is possible, and the last box received by each chicken is:

```text
2 4 6
```

Hence the answer is:

```text
YES
2 4 6
```

For the fourth query ($4 : 2 : 1$), no way of splitting the $6$ boxes into $3$ contiguous, ordered segments produces totals in that exact ratio, so the answer is `NO`.