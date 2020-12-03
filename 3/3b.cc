#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> read_map()
{
    std::vector<std::string> result;
    std::string line;
    while (!std::cin.eof()) {
        std::getline(std::cin, line);

        // trim the string
        auto trim_begin = line.end();
        auto trim_end = line.end();
        for (auto i = line.begin(); i != line.end(); ++i) {
            if (!std::isspace(*i)) {
                if (trim_begin == line.end()) {
                    trim_begin = i;
                }
                trim_end = i + 1;
            }
        }
        line = std::string(trim_begin, trim_end);

        if (line.length() > 0) {
            result.push_back(line);
        }
    }
    return result;
}

uint64_t test_slope(const std::vector<std::string>& map, int dx, int dy) {
    int width = (int) map[0].length();
    int height = (int) map.size();

    int x = 0;
    int y = 0;
    uint64_t trees = 0;

    for (x = 0, y = 0; y < height; x = (x + dx) % width, y = y + dy) {
        if (map[y][x] == '#') {
            trees += 1;
        }
    }

    return trees;
}

int main()
{
    std::vector<std::string> map = std::move(read_map());

    std::array<std::pair<int, int>, 5>  slopes{{
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    }};

    uint64_t result = 1;
    for (auto& [dx, dy] : slopes) {
        result *= test_slope(map, dx, dy);
    }
    std::cout << result << std::endl;
}