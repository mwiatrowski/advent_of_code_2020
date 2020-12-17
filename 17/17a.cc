#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::vector<std::vector<std::vector<char>>> space;

    int n = -1;
    for (size_t line_i = 0; true; ++line_i) {
        std::string line;
        std::getline(std::cin, line);
        if (line.length() == 0) {
            break;
        }
        if (n == -1) {
            n = line.length() + 12;
            space.resize(n);
            for (int i = 0; i < n; ++i) {
                space[i].resize(n);
                for (int j = 0; j < n; ++j) {
                    space[i][j].resize(n, '.');
                }
            }
        }

        for (size_t j = 0; j < line.size(); ++j) {
            space[6][line_i + 6][j + 6] = line[j];
        }
    }


    for (int cycle = 0; cycle < 6; ++cycle) {
        auto next_state = space;
        for (int z = 0; z < n; ++z) {
            for (int y = 0; y < n; ++y) {
                for (int x = 0; x < n; ++x) {
                    int occupied_neighbours = 0;
                    for (int dz = -1; dz <= 1; ++dz) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            for (int dx = -1; dx <= 1; ++dx) {
                                if (dz == 0 && dy == 0 && dx == 0) {
                                    continue;
                                }
                                if (z + dz < 0 || y + dy < 0 || x + dx < 0) {
                                    continue;
                                }
                                if (z + dz >= n || y + dy >= n || x + dx >= n) {
                                    continue;
                                }
                                if (space[z + dz][y + dy][x + dx] == '#') {
                                    occupied_neighbours += 1;
                                }
                            }
                        }
                    }

                    if (space[z][y][x] == '#' && (occupied_neighbours > 3 || occupied_neighbours < 2)) {
                        next_state[z][y][x] = '.';
                    }
                    if (space[z][y][x] == '.' && occupied_neighbours == 3) {
                        next_state[z][y][x] = '#';
                    }
                }
            }
        }

        space = next_state;
    }


    int active_cubes = 0;
    for (int z = 0; z < n; ++z) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (space[z][y][x] == '#') {
                    active_cubes += 1;
                }
            }
        }
    }

    std::cout << active_cubes << std::endl;
}
