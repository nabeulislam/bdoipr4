import random
random.seed(20240607)

lines = []
counter = [0]

def add(T, n, sumN, kmin, kmax, mode, style, tight, sym, cmax):
    counter[0] += 1
    if mode == 1:
        T = min(T, sumN // n)            # every test takes n, so T*n must fit in sumN
    T = max(1, min(T, 10000, sumN // 2))
    lines.append(f"gen {T} {n} {sumN} {kmin} {kmax} {mode} {style} {tight} {sym} {cmax} {counter[0]}")

lines.append("@subtask samples")
lines.append("manual sample.in")       # adjust to your TPS manual-test syntax

# ---------- subtask 1: T <= 10, n <= 1000  (70 tests)
lines.append("@subtask sub1")
for _ in range(70):
    kmax = random.choice([1, 2, 5, 50, 1000])
    add(T=random.choice([1, 1, 2, 5, 10]),
        n=random.choice([2, 3, 4, 5, 8, 20, 100, 1000]),
        sumN=10000,
        kmin=1, kmax=kmax,
        mode=random.choice([0, 1]),
        style=random.choice([-1, -1, 0, 1, 2, 3, 4]),
        tight=random.choice([0, 0, 1, 2]),
        sym=random.choice([0, 0, 0, 1, 2]),
        cmax=random.choice([2, 3, 10, 498]))

# ---------- subtask 2: n <= 1000, many tests  (110 tests)
lines.append("@subtask sub2")
lines.append("@include sub1")
for _ in range(110):
    n = random.choice([2, 3, 5, 10, 50, 300, 1000])
    T = random.choice([100, 1000, 5000, 10000]) if n <= 10 else random.choice([10, 50, 100])
    kmax = random.choice([1, 3, 10, 100, 1000])
    add(T=T, n=n, sumN=100000,
        kmin=1, kmax=kmax,
        mode=random.choice([0, 1]),
        style=random.choice([-1, -1, 0, 1, 2, 3, 4]),
        tight=random.choice([0, 0, 1, 2]),
        sym=random.choice([0, 0, 0, 1, 2]),
        cmax=random.choice([2, 5, 50, 498]))

# ---------- subtask 3: full constraints  (120 tests)
lines.append("@subtask sub3")
lines.append("@include sub2")
for _ in range(120):
    if random.random() < 0.6:
        n = random.choice([100000, 100000, 50000, 20000, 5000])
        T = 1 if n == 100000 else random.choice([1, 2, 5, 10])
    else:
        n = random.choice([10, 100, 1000])
        T = random.choice([100, 1000, 10000])
    kmax = random.choice([1, 2, 10, 500, 1000])
    add(T=T, n=n, sumN=100000,
        kmin=1, kmax=kmax,
        mode=random.choice([0, 1, 1]),
        style=random.choice([-1, 0, 1, 2, 3, 4]),
        tight=random.choice([0, 1, 2]),
        sym=random.choice([0, 0, 0, 1, 2]),
        cmax=random.choice([2, 20, 333, 498]))

open("data", "w").write("\n".join(lines) + "\n")
print(counter[0] + 1, "tests (including the sample)")