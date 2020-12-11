#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


const char FLOOR    = '.';
const char EMPTY    = 'L';
const char OCCUPIED = '#';


const std::vector<std::pair<int, int>> ADJACENT = {
    {-1, -1}, {-1,  0}, {-1,  1},
    { 0, -1},           { 0,  1},
    { 1, -1}, { 1,  0}, { 1,  1}
};


int main()
{
    std::vector<std::vector<char>> seats;
    while (std::cin.good()) {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() > 0) {
            seats.push_back({});
            for (char c : line) {
                seats.back().push_back(c);
            }
        }
    }

    int rows = seats.size();
    int cols = seats.front().size();

    while (true) {
        std::vector<std::vector<char>> new_seats = seats;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (seats[row][col] == FLOOR) {
                    continue;
                }

                int occupied = 0;
                for (const auto [d_row, d_col] : ADJACENT) {
                    int i_row = row + d_row;
                    int i_col = col + d_col;

                    while (i_row >= 0 && i_row < rows && i_col >= 0 && i_col < cols) {
                        if (seats[i_row][i_col] == FLOOR) {
                            i_col += d_col;
                            i_row += d_row;
                            continue;
                        } else {
                            if (seats[i_row][i_col] == OCCUPIED) {
                                occupied += 1;
                            }
                            break;
                        }
                    }
                }

                if (seats[row][col] == EMPTY && occupied == 0) {
                    new_seats[row][col] = OCCUPIED;
                } else if (seats[row][col] == OCCUPIED && occupied >= 5) {
                    new_seats[row][col] = EMPTY;
                }
            }
        }

        if (seats == new_seats) {
            break;
        }
        seats = new_seats;
    }

    int occupied_stable = 0;
    for (const auto& row : seats) {
        for (const auto& seat : row) {
            if (seat == OCCUPIED) {
                occupied_stable += 1;
            }
        }
    }

    std::cout << occupied_stable << std::endl;
}
