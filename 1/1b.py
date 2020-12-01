from collections import Counter
import sys

entries = []
try:
    while True:
        entries.append(int(input()))
except:
    pass

entries_counted = Counter(entries)

for i, a in enumerate(entries):
    for b in entries[i+1:]:
        c = 2020 - a - b
        required = 1 + (1 if a == c else 0) + (1 if b == c else 0)
        if entries_counted[c] >= required:
            print(a * b * c)
            sys.exit(0)
