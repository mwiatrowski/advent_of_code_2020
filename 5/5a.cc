#include <iostream>
#include <string>


uint64_t get_seat_id(const std::string& boarding_pass)
{
    uint64_t id = 0;
    for (const char& c : boarding_pass) {
        if (c == 'F' || c == 'L') {
            id = id * 2;
        } else if (c == 'B' || c == 'R') {
            id = id * 2 + 1;
        }
    }
    return id;
}

int main()
{
    uint64_t highest_id = 0;
    std::string line;

    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        uint64_t id = get_seat_id(line);
        if (id > highest_id) {
            highest_id = id;
        }
    }

    std::cout << highest_id << std::endl;
}
