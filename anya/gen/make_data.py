#!/usr/bin/env python3

def emit_subtask_tests(prefix, max_n, max_q, max_v, count, force_no_upd=False):
    lines = []
    modes = [
        ("hand_small",   50),
        ("bit_edge",     50),
        ("index_edge",   50),
        ("max_overflow", 15),
        ("random",       50),
        ("random",       95), # Update-heavy
        ("random",       5),  # Query-heavy
    ]
    for i in range(1, count + 1):
        mode, upd = modes[(i - 1) % len(modes)]
        if force_no_upd:
            upd = 0
        # Vary N and Q on the first few tests of each subtask for edge coverage
        if i == 1:
            n, q = 1, 1
        elif i == 2:
            n, q = 1, min(20, max_q)
        elif i == 3:
            n, q = min(2, max_n), min(50, max_q)
        elif i <= 8:
            n, q = min(100, max_n), min(200, max_q)
        else:
            n, q = max_n, max_q

        lines.append(f"gen {mode} {n} {q} {max_v} {upd} {prefix}_{i:03d}")
    return "\n".join(lines)

out = []

# Subtask 0: Samples
out.append("@subtask samples")
out.append("manual sample-01.in\n")

# Subtask 1: 50 tests (N, Q <= 1000, V <= 10^4)
out.append("@subtask sub1")
out.append(emit_subtask_tests("s1", 1000, 1000, 10000, 50) + "\n")

# Subtask 2: 50 new tests (N, Q <= 5000, V <= 10^6)
out.append("@subtask sub2")
out.append("@include sub1")
out.append(emit_subtask_tests("s2", 5000, 5000, 1000000, 50) + "\n")

# Subtask 3: 60 tests (N, Q <= 2e5, V <= 10^7, Type 1 only)
out.append("@subtask sub3")
out.append(emit_subtask_tests("s3", 200000, 200000, 10000000, 60, force_no_upd=True) + "\n")

# Subtask 4: 80 new tests (N, Q <= 2e5, V <= 10^7)
out.append("@subtask sub4")
out.append("@include sub2")
out.append("@include sub3")
out.append(emit_subtask_tests("s4", 200000, 200000, 10000000, 80) + "\n")

# Subtask 5: 120 new tests (N, Q <= 2e5, V <= 10^8) -> Total 360 tests
out.append("@subtask sub5")
out.append("@include sub4")
out.append(emit_subtask_tests("s5", 200000, 200000, 100000000, 120) + "\n")

print("\n".join(out))