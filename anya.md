# Anya and Prime Numbers

<p align="center">
  <img src="Anya_Forger_Anime.png" width="100">
</p>

Anya has sat for her mid-term exam in her school, Eden Academy. She must achieve all the stella stars to keep her family together and save world peace. Otherwise, Loid's "Operation Strix" will fail. The students next to her are struggling to answer the questions, so she can't take any worthy help from her telepathy ability. Help her to find the answers.

She is given an array $A$ with $N$ integers. Let's denote:

$$\pi(x) = \text{the number of prime numbers from } 1 \text{ to } x.$$

There are $Q$ questions (queries) to answer, of two types:

- `1 l r` — Output $\sum_{i=l}^{r} \pi(A_i)$.
- `2 u v` — Update $A_u := v$.

Help Anya cook in her exam and make Damian fall for her, making Operation Strix succeed.

## Input Format

- Line 1: a single integer $N$.
- Line 2: $N$ distinct integers $A_1, A_2, \dots, A_N$.
- Line 3: a single integer $Q$.
- Lines $3+i$ ($1 \le i \le Q$): the $i$-th query, in one of the following forms:
  - `1 l r` — a query of type $1$.
  - `2 u v` — a query of type $2$.

## Output Format

For every query of type $1$, print one integer: $\sum_{i=l}^{r} \pi(A_i)$, where $\pi(A_i)$ is the number of **prime numbers** from $1$ to $A_i$.

Print the answers in the order the queries are given.

## Constraints

- $1 \le N \le 2 \times 10^5$
- $1 \le Q \le 2 \times 10^5$
- $1 \le A_i \le 10^8$
- $A_i \ne A_j$ for $i \ne j$ ($1 \le i, j \le N$)
- $1 \le l \le r \le N$
- $1 \le u \le N$
- $1 \le v \le 10^8$

## Subtasks

| Subtask | Points |    $N$     |    $Q$     |   $A_i$    |    $v$     | Additional Constraints |
| :-----: | :----: | :--------: | :--------: | :--------: | :--------: | ---------------------- |
|    0    |   0    |     -      |     -      |     -      |     -      | The examples |
|    1    |   10   | $\le 1000$ | $\le 1000$ | $\le 10^4$ | $\le 10^4$ | No additional constraints. |
|    2    |   15   | $\le 5000$ | $\le 5000$ | $\le 10^6$ | $\le 10^6$ | No additional constraints. |
|    3    |   20   |     -      |     -      | $\le 10^7$ |     -      | There are no type $2$ queries. |
|    4    |   25   |     -      |     -      | $\le 10^7$ | $\le 10^7$ | No additional constraints. |
|    5    |   30   |     -      |     -      | $\le 10^8$ | $\le 10^8$ | No additional constraints. |

All other constraints are the same as in the Constraints section.

## Example

**Input:**

```text
10
4 3 0 50 49 1 3 4 4 3
8
1 5 6
1 4 4
1 9 9
2 7 50
1 2 8
1 8 9
2 1 3
2 9 3
```

**Output:**

```text
15
15
2
49
4
```

## Explanation

The initial array is $A = [4, 3, 0, 50, 49, 1, 3, 4, 4, 3]$. Useful values: $\pi(0) = \pi(1) = 0$, $\pi(3) = \pi(4) = 2$, $\pi(49) = \pi(50) = 15$.

1. `1 5 6`: $\pi(49) + \pi(1) = 15 + 0 = 15$.
2. `1 4 4`: $\pi(50) = 15$.
3. `1 9 9`: $\pi(4) = 2$.
4. `2 7 50`: $A_7$ becomes $50$, so the array is $[4, 3, 0, 50, 49, 1, 50, 4, 4, 3]$.
5. `1 2 8`: the values are $3, 0, 50, 49, 1, 50, 4$, so the answer is $2 + 0 + 15 + 15 + 0 + 15 + 2 = 49$.
6. `1 8 9`: $\pi(4) + \pi(4) = 2 + 2 = 4$.
7. `2 1 3`: $A_1$ becomes $3$.
8. `2 9 3`: $A_9$ becomes $3$.

Thus the complete output is $15, 15, 2, 49, 4$.