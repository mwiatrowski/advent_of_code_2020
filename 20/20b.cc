#include <array>
#include <assert.h>
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


const int TILE_SIZE = 10;
int MATRIX_SIZE = 12;
int NUMBER_OF_TILES = MATRIX_SIZE * MATRIX_SIZE;
int MAP_SIZE = MATRIX_SIZE * (TILE_SIZE - 2);


std::vector<std::string> SEA_MONSTER{
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   "
};


using Border = std::bitset<TILE_SIZE>;
using Image = std::array<std::string, TILE_SIZE>;


struct Tile {
    int id;
    Image image;
};


struct TileSelection {
    int index;
    int id;
    int rotation;
    bool flipped;
    Image image;
    std::array<Border, 4> borders;
};


std::array<Border, 4> get_borders(const Image& image) {
    std::array<Border, 4> borders;

    for (int i = 0; i < TILE_SIZE; ++i) {
        borders[0][i] = '#' == image[0][i];
        borders[1][i] = '#' == image[i][TILE_SIZE - 1];
        borders[2][i] = '#' == image[TILE_SIZE - 1][TILE_SIZE - 1 - i];
        borders[3][i] = '#' == image[TILE_SIZE - 1 - i][0];
    }

    return borders;
}


Border reversed(const Border& original) {
    Border result;
    for (int i = 0; i < TILE_SIZE; ++i) {
        result[i] = original[TILE_SIZE - 1 - i];
    }
    return result;
}


Image transformed(const Image& original, int rotation, bool flipped) {
    auto image_transformed = original;

    for (int y = 0; y < TILE_SIZE; ++y) {
        for (int x = 0; x < TILE_SIZE; ++x) {
            int img_x = x;
            int img_y = y;

            for (int i = 0; i < rotation; ++i) {
                int tmp = img_y;
                img_y = img_x;
                img_x = TILE_SIZE - 1 - tmp;
            }
            if (flipped) {
                int tmp = img_y;
                img_y = img_x;
                img_x = tmp;
            }

            image_transformed[y][x] = original[img_y][img_x];
        }
    }

    return image_transformed;
}


int main(int argc, char** argv)
{
    if (argc > 1) {
        MATRIX_SIZE = std::stoi(argv[1]);
        NUMBER_OF_TILES = MATRIX_SIZE * MATRIX_SIZE;
        MAP_SIZE = MATRIX_SIZE * (TILE_SIZE - 2);
    }

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

        std::getline(std::cin, line);
    }


    std::vector<std::vector<TileSelection>> tile_arrangement(MATRIX_SIZE);
    for (auto& row : tile_arrangement) {
        row.resize(MATRIX_SIZE);
    }
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

            const Tile& tile = tiles[tile_nr];

            int x = next_tile % MATRIX_SIZE;
            int y = next_tile / MATRIX_SIZE;

            for (int flip = 0; flip <= 1; ++flip) {
                bool flipped = (flip == 0);
                for (int rotation = 0; rotation < 4; ++rotation) {
                    bool fits = true;

                    Image transformed_image = transformed(tile.image, rotation, flipped);
                    std::array<Border, 4> borders = get_borders(transformed_image);

                    if (x > 0) {
                        const TileSelection& left_tile = tile_arrangement[y][x - 1];
                        Border right_border = left_tile.borders[1];
                        Border left_border = borders[3];

                        if (right_border != reversed(left_border)) {
                            fits = false;
                        }
                    }

                    if (fits && y > 0) {
                        const TileSelection& top_tile = tile_arrangement[y - 1][x];
                        Border bottom_border = top_tile.borders[2];
                        Border top_border = borders[0];

                        if (bottom_border != reversed(top_border)) {
                            fits = false;
                        }
                    }

                    if (fits) {
                        TileSelection new_selection;
                        new_selection.index = tile_nr;
                        new_selection.id = tile.id;
                        new_selection.rotation = rotation;
                        new_selection.flipped = flipped;
                        new_selection.image = transformed_image;
                        new_selection.borders = borders;
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


    std::vector<std::string> map(MAP_SIZE);
    for (auto& row : map) {
        row.resize(MAP_SIZE);
    }

    for (int row = 0; row < MATRIX_SIZE; ++row) {
        for (int col = 0; col < MATRIX_SIZE; ++col) {
            const TileSelection& selected = tile_arrangement[row][col];
            const auto& image = selected.image;

            int off_y = row * (TILE_SIZE - 2);
            int off_x = col * (TILE_SIZE - 2);

            for (int y = 0; y < TILE_SIZE - 2; ++y) {
                for (int x = 0; x < TILE_SIZE - 2; ++x) {
                    map[off_y + y][off_x + x] = image[y + 1][x + 1];
                }
            }
        }
    }

    for (int flip = 0; flip <= 1; ++flip) {
        bool flipped = (flip == 0);
        for (int rotation = 0; rotation < 4; ++rotation) {
            std::vector<std::string> map_transformed = map;
            for (int y = 0; y < MAP_SIZE; ++y) {
                for (int x = 0; x < MAP_SIZE; ++x) {
                    int x2 = x;
                    int y2 = y;

                    for (int i = 0; i < rotation; ++i) {
                        int tmp = y2;
                        y2 = x2;
                        x2 = MAP_SIZE - 1 - tmp;
                    }

                    if (flipped) {
                        int tmp = x2;
                        x2 = y2;
                        y2 = tmp;
                    }

                    map_transformed[y][x] = map[y2][x2];
                }
            }

            std::vector<std::vector<bool>> has_sea_monster(MAP_SIZE);
            for (auto& row : has_sea_monster) {
                row.resize(MAP_SIZE, false);
            }

            int found_monsters = 0;
            for (int row = 0; row < MAP_SIZE; ++row) {
                for (int col = 0; col < MAP_SIZE; ++col) {
                    if (row + SEA_MONSTER.size() > MAP_SIZE) {
                        continue;
                    }
                    if (col + SEA_MONSTER.front().size() > MAP_SIZE) {
                        continue;
                    }

                    bool monster_here = true;
                    for (int y = 0; y < SEA_MONSTER.size() && row + y < MAP_SIZE && monster_here; ++y) {
                        for (int x = 0; x < SEA_MONSTER.front().size() && col + x < MAP_SIZE && monster_here; ++x) {
                            if (SEA_MONSTER[y][x] == '#' && map_transformed[row + y][col + x] != '#') {
                                monster_here = false;
                            }
                        }
                    }

                    if (monster_here) {
                        for (int y = 0; y < SEA_MONSTER.size(); ++y) {
                            for (int x = 0; x < SEA_MONSTER.front().size(); ++x) {
                                if (SEA_MONSTER[y][x] == '#') {
                                    has_sea_monster[row + y][col + x] = true;
                                }
                            }
                        }

                        found_monsters += 1;
                    }
                }
            }

            if (found_monsters > 0) {
                int result = 0;
                for (int row = 0; row < MAP_SIZE; ++row) {
                    for (int col = 0; col < MAP_SIZE; ++col) {
                        if (map_transformed[row][col] == '#' && !has_sea_monster[row][col]) {
                            result += 1;
                        }
                    }
                }

                std::cout << result << std::endl;
            }
        }
    }
}
