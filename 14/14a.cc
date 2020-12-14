#include <iostream>
#include <map>
#include <string>
#include <vector>


int main()
{
    std::map<uint64_t, uint64_t> memory;

    uint64_t mask       = 0;
    uint64_t const_bits = 0;

    while (std::cin.good()) {
        std::string lhs, eq, rhs;
        std::cin >> lhs >> eq >> rhs;
        if (std::cin.fail()) {
            break;
        }

        if (lhs == "mask") {
            mask       = 0;
            const_bits = 0;
            for (const char& bit : rhs) {
                mask = (mask << 1) + (bit == 'X' ? 1 : 0);
                const_bits = (const_bits << 1) + (bit == '1' ? 1 : 0);
            }
        } else {
            uint64_t address = std::stoi(lhs.substr(4, lhs.length() - 5));
            uint64_t value = std::stol(rhs);
            uint64_t masked_value = (value & mask) + const_bits;
            memory[address] = masked_value;
        }
    }

    uint64_t total = 0;
    for (auto [addr, val] : memory) {
        total += val;
    }
    std::cout << total << std::endl;
}
