# Number Roulette

*"This town ain't big enough for the two of us."*

Arthur Morgan has been challenged to a game of Russian Roulette. However, this isn't normal Russian Roulette — it is played on an $N \times M$ grid where each cell $(r, c)$ has an integer value $A_{r,c}$.

Before the game starts, Arthur chooses a positive integer $X$:

- A cell $(r, c)$ is **safe** if $A_{r,c} \ge X$.
- A cell $(r, c)$ is **unsafe** if $A_{r,c} < X$.

Connected **safe** cells (sharing an edge up, down, left, or right) form a **safe zone**. The size of a safe zone is the total number of cells in it.

Arthur starts at $(1, 1)$ and can move up, down, left, or right. To win the game, he must reach any cell in a safe zone of size **at least $S$**, while stepping on **at most $K$ unsafe cells** along his path (including $(1, 1)$ if it is unsafe).

Find the **maximum integer $X$** Arthur can choose to win the game, or output `0` if it is impossible.

## Input Format

- Line 1: four integers $N$, $M$, $K$ and $S$.
- Line $1+r$ ($1 \le r \le N$): $M$ integers $A_{r,1}, A_{r,2}, \dots, A_{r,M}$.

## Output Format

Print a single integer — the maximum valid $X$, or `0` if Arthur cannot win.

## Constraints

- $1 \le N, M \le 500$
- $0 \le K \le N \times M$
- $1 \le S \le N \times M$
- $1 \le A_{r,c} \le 10^9$

## Subtasks

| Subtask | Points |    $N$    |    $M$    |    $K$    |  $S$  |    $A_{r,c}$    | Additional Constraints |
| :-----: | :----: | :-------: | :-------: | :-------: | :---: | :-------------: | ---------------------- |
|    0    |    0   |     -     |     -     |     -     |   -   |        -        | The examples |
|    1    |   20   | $\le 40$  | $\le 40$  |     -     |   -   |    $\le 50$     | No additional constraints. |
|    2    |   20   |     -     |     -     |     -     | $=1$  | $\in \{1, 2\}$  | An optimal path only moves **Down** and **Right**. |
|    3    |   25   |     -     |     -     | $= ~N~ \times ~M~$ | - |        -        | No additional constraints. |
|    4    |   35   |     -     |     -     |     -     |   -   |        -        | No additional constraints. |

All other constraints are the same as in the Constraints section.

## Example

**Input:**

```text
3 4 1 3
9 2 8 8
1 1 2 9
4 4 1 7
```

**Output:**

```text
8
```

## Explanation

The grid is:

```text
9 2 8 8
1 1 2 9
4 4 1 7
```

Choose $X = 8$. The safe cells are $(1,1)$, $(1,3)$, $(1,4)$ and $(2,4)$.

- $(1,1)$ forms a safe zone of size $1$.
- $(1,3)$, $(1,4)$ and $(2,4)$ are connected and form a safe zone of size $3 \ge S$.

Arthur starts at $(1,1)$, steps onto the unsafe cell $(1,2)$ (value $2 < 8$), and then reaches $(1,3)$. He stepped on $1 \le K$ unsafe cell, so he wins.

Choose $X = 9$. Only $(1,1)$ and $(2,4)$ are safe, and each forms a zone of size $1 < S$, so Arthur cannot win. Therefore the maximum valid $X$ is $8$.