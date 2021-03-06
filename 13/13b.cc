#include <iostream>
#include <string>
#include <vector>


struct EEA_result {
    int64_t gcd;
    int64_t x;
    int64_t y;
};

EEA_result EEA(int64_t a, int64_t b)
{
    int64_t x = 1;
    int64_t y = 0;
    int64_t r = 0;
    int64_t s = 1;

    if (b > a) {
        std::swap(a, b);
    }

    while (b != 0) {
        int64_t c = a % b;
        int64_t q = a / b;
        a = b;
        b = c;

        int64_t r2 = r;
        int64_t s2 = s;
        r = x - q * r;
        s = y - q * s;
        x = r2;
        y = s2;
    }

    return {a, y, x};
}


int64_t chinese_remainder_theorem(const std::vector<std::pair<int64_t, int64_t>>& constraints)
{
    int64_t M = 1;
    for (auto [n, y] : constraints) {
        M *= n;
    }

    int64_t x = 0;
    for (auto [n, y] : constraints) {
        int64_t Mi = M / n;
        EEA_result eea = EEA(n, Mi);
        if (eea.gcd != 1) {
            throw std::exception("Assertion error");
        }

        x += (eea.y * Mi) * y;
    }
    x = ((x % M) + M) % M;

    return x;
}


std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> result;

    size_t chunk_begin = 0;
    while (true) {
        size_t chunk_end = str.find(delimiter, chunk_begin);

        if (chunk_end != std::string::npos) {
            result.push_back(str.substr(chunk_begin, chunk_end - chunk_begin));
            chunk_begin = chunk_end + 1;
        } else {
            result.push_back(str.substr(chunk_begin));
            break;
        }
    }

    return result;
}


int main()
{
    std::string bus_ids;
    std::getline(std::cin, bus_ids);
    std::getline(std::cin, bus_ids);
    std::vector<std::string> bus_ids_split = split(bus_ids, ',');

    std::vector<std::pair<int64_t, int64_t>> constraints;

    for (int64_t i = 0; i < bus_ids_split.size(); ++i) {
        int64_t bus_id;
        try {
            bus_id = std::stol(bus_ids_split[i]);
        } catch(std::invalid_argument) {
            continue;
        }

        int64_t rem = ((bus_id - i) % bus_id + bus_id) % bus_id;
        constraints.push_back({bus_id, rem});
    }

    int64_t result = chinese_remainder_theorem(constraints);

    std::cout << result << std::endl;
}
