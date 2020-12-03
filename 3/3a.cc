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

int main()
{
    std::vector<std::string> map = std::move(read_map());

    int width = (int) map[0].length();
    int height = (int) map.size();

    int x = 0;
    int y = 0;

    int trees = 0;
    for (x = 0, y = 0; y < height; x = (x + 3) % width, y = y + 1) {
        if (map[y][x] == '#') {
            trees += 1;
        }
    }

    std::cout << trees << std::endl;
}