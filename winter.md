# Winter Charity

A winter cloth distribution campaign will be held in the city of BugBlossoms. There are two orphanages, each with $n$ rooms separated by a river. It takes $k$ units of time to cross the river, and the rooms in each orphanage are numbered from left to right, starting from $1$.

As Ad-Duha is managing the campaign alone, she has decided to keep all the winter clothing packages in a single room due to a lack of volunteers. The children from every occupied room in both orphanages must come to that room to collect their winter clothes. Ad-Duha wants to **minimize the maximum time** any child spends reaching the room containing the packages.

If the packages are located in room $i$ of an orphanage and a child is in room $j$:

- of the **same** orphanage, the child takes $|i-j|$ units of time to reach the packages.
- of the **other** orphanage, the child must cross the river, which takes $k+i+j$ units of time.

Ad-Duha felt sad that some children had to cross the river to receive their winter clothes, so she decided to give them books, flowers and chocolates as well.

Each character `1` in the strings represents exactly one child. Ad-Duha also has $m$ gift boxes. After the room for the packages is chosen, the children are split into two groups:

- **Group A:** the children who live in the same orphanage as the packages. Let $a$ be their number.
- **Group B:** the children who live in the other orphanage. Let $b$ be their number.

Each child in Group A gets exactly $x$ boxes, and each child in Group B gets exactly $y$ boxes, where:

- $x \ge 1$,
- $y \ge 2$,
- $y > x$.

The total $a \cdot x + b \cdot y$ must not be more than $m$. Ad-Duha wants to give away as many boxes as possible. Find the minimum number of boxes that remain ungifted.

## Input Format

The first line contains an integer $T$ — the number of test cases.

Each test case is described as follows:

- Line 1: three integers $n$, $k$ and $m$ — the number of rooms in each orphanage, the time required to cross the river, and the number of gift boxes, respectively.
- Line 2: a string of $n$ characters, each either `0` or `1`. This string represents the children staying in the rooms of the **first** orphanage. If the $i$-th character is `1`, a child stays in room $i$ of the first orphanage. Otherwise that room is empty.
- Line 3: a string of $n$ characters, each either `0` or `1`. This string represents the children staying in the rooms of the **second** orphanage, in the same way.

It is guaranteed that each of the two strings contains at least two `1`s, so whichever orphanage is chosen, $a \ge 1$ and $b \ge 2$.

It is also guaranteed that $a + 2b \le m$ for whichever orphanage is chosen. That is, both $c_1 + 2c_2 \le m$ and $c_2 + 2c_1 \le m$, where $c_1$ and $c_2$ are the numbers of `1`s in the first and second string.

## Output Format

For each test case, print the following three lines:

- Line 1: one integer — the minimum possible maximum travel time among all possible locations for the winter clothing packages.
- Line 2: two integers — the index of the orphanage and the index of the room where the packages should be placed. If there are multiple optimal answers, print any of them.
- Line 3: one integer — the minimum possible number of gift boxes left ungifted.

If the minimum time can be reached by placing the packages in orphanage 1 and also by placing them in orphanage 2, you may take either orphanage as the one with the packages when you compute $a$ and $b$. Any of the resulting answers for the third line is accepted.

**Every test case must print exactly three lines.** If you cannot compute some part, print `-1` in its place:

- Line 1 is the minimum requirement and must always be printed.
- If you do not print a valid room, print `-1 -1` on line 2.
- If you do not print the number of leftover boxes, print `-1` on line 3.

## Constraints

- $1 \le T \le 10^4$
- $1 \le n \le 10^5$
- $1 \le k \le 1000$
- $3 \le m \le 1000$
- The sum of $n$ over all test cases does not exceed $10^5$.

## Subtasks

| Subtask | Points |   $T$   |    $n$    | Additional Constraints                    |
| :-----: | :----: | :-----: | :-------: | ----------------------------------------- |
|    0    |    0   |    -    |     -     | The examples                              |
|    1    |   30   | $\le 10$ | $\le 10^3$ | No additional constraints.                |
|    2    |   30   |    -    | $\le 10^3$ | No additional constraints.                |
|    3    |   40   |    -    |     -     | No additional constraints.                |

All other constraints are the same as in the Constraints section.

## Scoring

Each test case in a file is scored separately, and the score of the file is the average over its test cases. For one test case:
 
- If you print the minimum possible maximum travel time on line 1, you get $30\%$ of the score.
- If you print a valid room on line 2 whose maximum travel time equals that minimum, you get another $30\%$ of the score.
- If you print the minimum number of ungifted boxes on line 3, you get the remaining $40\%$ of the score. The number is computed for the orphanage printed on line 2 (or for either orphanage, if the minimum time is reached by both).


## Example

**Input:**

```text
5
5 3 20
10100
00101
6 10 41
100001
010010
4 1 15
1110
0011
4 2 11
1101
0110
3 1 8
111
110
```

**Output:**

```text
7
2 1
0
16
1 1
1
5
2 1
1
6
1 1
0
4
1 1
1
```

## Explanation

**Test 1:** The first orphanage has children in rooms $1$ and $3$, and the second in rooms $3$ and $5$.

Placing the packages in room $1$ of the second orphanage:

- the children in the same orphanage need $|1-3| = 2$ and $|1-5| = 4$.
- the children in the first orphanage need $3+1+1 = 5$ and $3+1+3 = 7$.

The maximum is $7$, and no other room does better. Here $a = 2$ and $b = 2$. Give each of the $2$ children $4$ boxes and each of the $2$ children $6$ boxes. That uses $2 \cdot 4 + 2 \cdot 6 = 20$ boxes, so $0$ are left.

**Test 2:** Placing the packages in room $1$ of the first orphanage:

- the same-orphanage children need $0$ and $5$.
- the children from the second orphanage need $10+1+2 = 13$ and $10+1+5 = 16$.

The answer is $16$. Here $a = 2$ and $b = 2$. Give $9$ boxes and $11$ boxes. That uses $2 \cdot 9 + 2 \cdot 11 = 40$ boxes, so $1$ is left. Giving $10$ and $11$ would need $42 > 41$.