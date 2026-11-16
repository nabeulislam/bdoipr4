# Number Roulette



 *"This town ain't big enough for the two of us."*

Arthur Morgan has been challenged to a game of Russian Roulette. However, this isn't normal Russian Roulette—it is played on an $N \times M$ grid where each cell $(r, c)$ has an integer value $A_{r,c}$.

Before the game starts, Arthur chooses a positive integer $X$:
* A cell $(r, c)$ is **safe** if $A_{r,c} \ge X$.
* A cell $(r, c)$ is **unsafe** if $A_{r,c} < X$.

Connected **safe** cells (sharing an edge up, down, left, or right) form a **safe zone**. The size of a safe zone is the total number of cells in it.

Arthur starts at $(1, 1)$ and can move up, down, left, or right. To win the game, he must reach any cell in a **safe zone** of size **at least $S$**, while stepping on **at most $K$ unsafe cells** along his path (including $(1, 1)$ if it is unsafe).

Find the **maximum integer $X$** Arthur can choose to win the game, or output `0` if it is impossible.

---

## Input Format

* The first line contains four integers $N$, $M$, $K$, and $S$.
* The next $N$ lines each contain $M$ integers $A_{r,1}, A_{r,2}, \dots, A_{r,M}$.

---

## Output Format

Print a single integer — the maximum valid $X$, or `0` if Arthur cannot win.

---

## Constraints & Subtasks

* $1 \le N, M \le 500$
* $0 \le K \le N \times M$
* $1 \le S \le N \times M$
* $1 \le A_{r,c} \le 10^9$

| Subtask | Points | Additional Constraints |
| :--- | :--- | :--- |
| **1** | 20 | $N, M \le 40$, $A_{r,c} \le 50$ |
| **2** | 20 | $A_{r,c} \in \{1, 2\}$, $S = 1$, and an optimal path only moves **Down** and **Right** |
| **3** | 25 | $K = N \times M$ |
| **4** | 35 | No additional constraints |

---

## Sample 1

### Input
```text
3 4 1 3
9 2 8 8
1 1 2 9
4 4 1 7
```

### Output
```text
8
```