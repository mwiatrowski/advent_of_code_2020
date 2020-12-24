import sys


black_tiles = set()

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

    if (x, y) not in black_tiles:
        black_tiles.add((x, y))
    else:
        black_tiles.remove((x, y))


def nearby_tiles(tile):
    x, y = tile
    return [(x+1, y), (x+1, y+1), (x, y+1), (x-1, y), (x-1, y-1), (x, y-1)]

for day in range(100):
    white_tiles = dict()
    new_black_tiles = set()
    for tile in black_tiles:
        black_nearby_tiles = 0
        for neighbour in nearby_tiles(tile):
            if neighbour in black_tiles:
                black_nearby_tiles += 1
            else:
                white_tiles[neighbour] = 1 + white_tiles.get(neighbour, 0)
        if black_nearby_tiles in [1, 2]:
            new_black_tiles.add(tile)
    for tile, counter in white_tiles.items():
        if counter == 2:
            new_black_tiles.add(tile)

    black_tiles = new_black_tiles


print(len(black_tiles))
