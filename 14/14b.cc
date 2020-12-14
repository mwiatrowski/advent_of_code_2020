#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>


int main()
{
    std::map<uint64_t, uint64_t> memory;

    std::function<void(std::string&, uint64_t)> assign_value;
    assign_value = [&](std::string& address_str, uint64_t value) {
        size_t x_pos = address_str.find('X');
        // std::cout << "X in " << address_str << " at " << x_pos << std::endl;

        if (x_pos == std::string::npos) {
            uint64_t address = std::stoll(address_str, 0, 2);
            memory[address] = value;
        } else {
            address_str[x_pos] = '0';
            assign_value(address_str, value);
            address_str[x_pos] = '1';
            assign_value(address_str, value);
            address_str[x_pos] = 'X';
        };
    };

    std::string mask = "000000000000000000000000000000000000";

    while (std::cin.good()) {
        std::string lhs, eq, rhs;
        std::cin >> lhs >> eq >> rhs;
        if (std::cin.fail()) {
            break;
        }

        if (lhs == "mask") {
            mask = rhs;
        } else {
            uint64_t address = std::stoi(lhs.substr(4, lhs.length() - 5));
            uint64_t value = std::stol(rhs);
            std::bitset<36> address_binary = std::bitset<36>(address);

            std::string masked_address = mask;
            for (size_t i = 0; i < 36; ++i) {
                if (mask[i] == '0') {
                    masked_address[i] = '0' + address_binary[35 - i];
                }
            }

            assign_value(masked_address, value);
        }
    }

    uint64_t total = 0;
    for (auto [addr, val] : memory) {
        total += val;
    }
    std::cout << total << std::endl;
}
