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

    std::sort(adapters.begin(), adapters.end());

    int ones   = 0;
    int threes = 0;

    int last = 0;
    for (size_t i = 0; i < adapters.size(); ++i) {
        int diff = adapters[i] - last;
        last = adapters[i];

        if (diff == 1) {
            ones += 1;
        } else if (diff == 3) {
            threes += 1;
        }
    }
    threes += 1;

    std::cout << (ones * threes) << std::endl;
}