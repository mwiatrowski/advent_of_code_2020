#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::vector<int> adapters;

    int adapter;
    while (std::cin.good()) {
        std::cin >> adapter;
        if (std::cin.good()) {
            adapters.push_back(adapter);
        }
    }

    adapters.push_back(0);
    std::sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters.back() + 3);

    std::vector<uint64_t> arrangements(adapters.size(), 0);
    arrangements[0] = 1;

    for (size_t i = 0; i < arrangements.size(); ++i) {
        for (size_t j = i + 1; j < arrangements.size(); ++j) {
            if (adapters[j] - adapters[i] > 3) {
                break;
            } else {
                arrangements[j] += arrangements[i];
            }
        }
    }

    std::cout << arrangements.back() << std::endl;
}
