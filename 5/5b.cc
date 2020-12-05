#include <array>
#include <iostream>
#include <string>


uint32_t get_seat_id(const std::string& boarding_pass)
{
    uint32_t id = 0;
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
    std::array<bool, 1024> spotted_ids;
    spotted_ids.fill(false);

    std::string line;
    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        if (line.size() == 0) {
            continue;
        }
        uint32_t id = get_seat_id(line);
        spotted_ids[id] = true;
    }

    bool found_first = false;
    for (size_t id = 0; id < 1024; ++id) {
        if (spotted_ids[id] == true) {
            found_first = true;
        }
        if (spotted_ids[id] == false) {
            if (found_first) {
                std::cout << id << std::endl;
                break;
            }
        }
    }
}
