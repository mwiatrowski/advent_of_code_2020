#include <iostream>
#include <string>
#include <vector>


size_t find_invalid_number(const std::vector<int64_t>& numbers, int preamble_length)
{
    for (size_t i = preamble_length; i < numbers.size(); ++i) {
        bool is_sum = false;
        for (int j = i - preamble_length; j < i && (!is_sum); ++j) {
            for (int k = j + 1; k < i; ++k) {
                if (numbers[j] + numbers[k] == numbers[i]) {
                    is_sum = true;
                    break;
                }
            }
        }
        if (!is_sum) {
            return i;
        }
    }
}


int main(int argc, char** argv)
{
    const int preamble_length = std::stoi(argv[1]);

    std::vector<int64_t> numbers;
    while (std::cin.good()) {
        int64_t number;
        std::cin >> number;
        if (std::cin.good()) {
            numbers.push_back(number);
        }
    }

    size_t n = find_invalid_number(numbers, preamble_length);

    std::vector<int64_t> partial_sums(n, 0);
    for (size_t i = 1; i < n; ++i) {
        partial_sums[i] = partial_sums[i - 1] + numbers[i - 1];
    }

    size_t range_start = -1;
    size_t range_end   = -1;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 2; j < n; ++j) {
            if (partial_sums[j] - partial_sums[i] == numbers[n]) {
                range_start = i;
                range_end   = j;
                break;
            }
        }
        if (range_start == i) {
            break;
        }
    }

    int64_t min_num = numbers[range_start];
    int64_t max_num = numbers[range_start];
    for (size_t i = range_start; i < range_end; ++i) {
        if (numbers[i] < min_num) {
            min_num = numbers[i];
        }
        if (numbers[i] > max_num) {
            max_num = numbers[i];
        }
    }

    std::cout << (min_num + max_num) << std::endl;
}
