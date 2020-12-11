#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


const std::vector<std::pair<int, int>> ADJACENT = {
    {-1, -1}, {-1,  0}, {-1,  1},
    { 0, -1},           { 0,  1},
    { 1, -1}, { 1,  0}, { 1,  1}
};


int main()
{
    std::vector<std::vector<char>> seats;
    seats.push_back({});
    while (std::cin.good()) {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() > 0) {
            seats.push_back({'.'});
            for (char c : line) {
                seats.back().push_back(c);
            }
            seats.back().push_back('.');
        }
    }
    seats[0] = std::vector<char>(seats[1].size(), '.');
    seats.push_back(seats[0]);

    while (true) {
        std::vector<std::vector<char>> new_seats = seats;
        for (size_t row = 1; row < seats.size() - 1; ++row) {
            for (size_t col = 1; col < seats[row].size() - 1; ++col) {
                if (seats[row][col] == '.') {
                    continue;
                }
                int occupied = 0;
                for (auto [d_row, d_col] : ADJACENT) {
                    if (seats[row + d_row][col + d_col] == '#') {
                        occupied += 1;
                    }
                }
                if (seats[row][col] == 'L' && occupied == 0) {
                    new_seats[row][col] = '#';
                } else if (seats[row][col] == '#' && occupied >= 4) {
                    new_seats[row][col] = 'L';
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
            if (seat == '#') {
                occupied_stable += 1;
            }
        }
    }

    std::cout << occupied_stable << std::endl;
}
