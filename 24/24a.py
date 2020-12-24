import sys


flipped = set()

for line in sys.stdin:
    line = list(line.strip())
    if len(line) == 0:
        break

    x = 0
    y = 0
    while len(line) > 0:
        move = str(line.pop(0))
        if move in ['n', 's']:
            move += line.pop(0)

        if move == 'e':
            x += 1
        elif move == 'se':
            x += 1
            y += 1
        elif move == 'sw':
            y += 1
        elif move == 'w':
            x -= 1
        elif move == 'nw':
            x -= 1
            y -= 1
        elif move == 'ne':
            y -= 1

    if (x, y) not in flipped:
        flipped.add((x, y))
    else:
        flipped.remove((x, y))

print(len(flipped))
