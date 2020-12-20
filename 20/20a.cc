#include <array>
#include <assert.h>
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


const int TILE_SIZE = 10;
const int MATRIX_SIZE = 12;
const int NUMBER_OF_TILES = MATRIX_SIZE * MATRIX_SIZE;


using Border = std::bitset<TILE_SIZE>;


Border reversed(const Border& original) {
    Border result;
    for (int i = 0; i < TILE_SIZE; ++i) {
        result[i] = original[TILE_SIZE - 1 - i];
    }
    return result;
}


struct Tile {
    int id;
    std::array<Border, 4> borders;
    std::array<std::string, TILE_SIZE> image;
};


struct TileSelection {
    int index;
    int rotation;
    bool flipped;
};


Border get_top_border(const Tile& tile, int rotation, bool flipped) {
    int index = (0 + rotation + (flipped ? 3 : 0)) % 4;
    const Border& border = tile.borders[index];
    return flipped ? reversed(border) : border;
}

Border get_right_border(const Tile& tile, int rotation, bool flipped) {
    int index = (1 + rotation + (flipped ? 1 : 0)) % 4;
    const Border& border = tile.borders[index];
    return flipped ? reversed(border) : border;
}

Border get_bottom_border(const Tile& tile, int rotation, bool flipped) {
    int index = (2 + rotation + (flipped ? 3 : 0)) % 4;
    const Border& border = tile.borders[index];
    return flipped ? reversed(border) : border;
}

Border get_left_border(const Tile& tile, int rotation, bool flipped) {
    int index = (3 + rotation + (flipped ? 1 : 0)) % 4;
    const Border& border = tile.borders[index];
    return flipped ? reversed(border) : border;
}


int main()
{
    std::vector<Tile> tiles;
    tiles.resize(NUMBER_OF_TILES);

    for (int tile_nr = 0; tile_nr < NUMBER_OF_TILES; ++tile_nr) {
        Tile& tile = tiles[tile_nr];

        std::string line;
        std::getline(std::cin, line);
        tile.id = std::stoi(line.substr(5, line.size() - 6));

        for (int row = 0; row < TILE_SIZE; ++row) {
            std::getline(std::cin, tile.image[row]);
            assert(tile.image[row].length() == TILE_SIZE);
        }

        for (int i = 0; i < TILE_SIZE; ++i) {
            tile.borders[0][i] = '#' == tile.image[0][i];
            tile.borders[1][i] = '#' == tile.image[i][TILE_SIZE - 1];
            tile.borders[2][i] = '#' == tile.image[TILE_SIZE - 1][TILE_SIZE - 1 - i];
            tile.borders[3][i] = '#' == tile.image[TILE_SIZE - 1 - i][0];
        }

        std::getline(std::cin, line);
    }


    std::array<std::array<TileSelection, MATRIX_SIZE>, MATRIX_SIZE> tile_arrangement;
    std::vector<bool> is_used(NUMBER_OF_TILES, false);

    std::function<bool(int)> find_solution;
    find_solution = [&](int next_tile) {
        if (next_tile == NUMBER_OF_TILES) {
            return true;
        }

        for (int tile_nr = 0; tile_nr < NUMBER_OF_TILES; ++tile_nr) {
            if (is_used[tile_nr]) {
                continue;
            }

            int x = next_tile % MATRIX_SIZE;
            int y = next_tile / MATRIX_SIZE;

            for (int flip = 0; flip <= 1; ++flip) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    bool fits = true;

                    if (x > 0) {
                        const TileSelection& left_tile = tile_arrangement[y][x - 1];
                        Border right_border = get_right_border(tiles[left_tile.index], left_tile.rotation, left_tile.flipped);
                        Border left_border = get_left_border(tiles[tile_nr], rotation, flip);

                        if (right_border != reversed(left_border)) {
                            fits = false;
                        }
                    }

                    if (fits && y > 0) {
                        const TileSelection& top_tile = tile_arrangement[y - 1][x];
                        Border bottom_border = get_bottom_border(tiles[top_tile.index], top_tile.rotation, top_tile.flipped);
                        Border top_border = get_top_border(tiles[tile_nr], rotation, flip);

                        if (bottom_border != reversed(top_border)) {
                            fits = false;
                        }
                    }

                    if (fits) {
                        TileSelection new_selection{tile_nr, rotation, (flip == 1)};
                        tile_arrangement[y][x] = new_selection;
                        is_used[tile_nr] = true;

                        if (find_solution(next_tile + 1)) {
                            return true;
                        } else {
                            is_used[tile_nr] = false;
                        }
                    }
                }
            }
        }

        return false;
    };

    assert(find_solution(0));

    int64_t result = 1;
    result *= tiles[tile_arrangement[0][0].index].id;
    result *= tiles[tile_arrangement[0][MATRIX_SIZE - 1].index].id;
    result *= tiles[tile_arrangement[MATRIX_SIZE - 1][0].index].id;
    result *= tiles[tile_arrangement[MATRIX_SIZE - 1][MATRIX_SIZE - 1].index].id;

    std::cout << result << std::endl;
}
