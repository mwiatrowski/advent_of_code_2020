#include <iostream>
#include <string>
#include <vector>


int main(int argc, char** argv)
{
    const int PREAMBLE_LENGTH = std::stoi(argv[1]);

    std::vector<int64_t> numbers;
    while (std::cin.good()) {
        int64_t number;
        std::cin >> number;
        if (std::cin.good()) {
            numbers.push_back(number);
        }
    }

    for (size_t i = PREAMBLE_LENGTH; i < numbers.size(); ++i) {
        bool is_sum = false;
        for (int j = i - PREAMBLE_LENGTH; j < i && (!is_sum); ++j) {
            for (int k = j + 1; k < i; ++k) {
                if (numbers[j] + numbers[k] == numbers[i]) {
                    is_sum = true;
                    break;
                }
            }
        }
        if (!is_sum) {
            std::cout << numbers[i] << std::endl;
            return 0;
        }
    }
}
