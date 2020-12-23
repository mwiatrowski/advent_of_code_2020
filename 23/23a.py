cups = [int(c) for c in input().strip()]
N = len(cups)

def simulate_one_round():
    global cups
    current, removed, cups = cups[0], cups[1:4], cups[4:]
    dest = (current - 2 + N) % N + 1
    while True:
        try:
            dest_pos = cups.index(dest)
            break
        except ValueError:
            assert dest in removed
            dest = (dest - 2 + N) % N + 1
    cups = cups[:dest_pos] + [dest] + removed + cups[dest_pos + 1:] + [current]

for i in range(100):
    simulate_one_round()

one_pos = cups.index(1)
for cup in cups[one_pos + 1:] + cups[:one_pos]:
    print(cup, end='')
print()
