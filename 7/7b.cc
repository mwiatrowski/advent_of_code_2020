#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <functional>


int get_bag_code(std::string c1, std::string c2, std::map<std::string, int>& bags_types)
{
    std::string color = c1 + " " + c2;
    if (bags_types.count(color) > 0) {
        return bags_types[color];
    } else {
        int bag_code = bags_types.size();
        bags_types.insert({color, bag_code});
        return bag_code;
    }
}

int main()
{
    std::map<std::string, int> bags_types;
    std::vector<std::vector<std::pair<int, int>>> bags_inclusion;

    std::string line;
    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        std::stringstream line_stream(line);

        std::string c1, c2;
        std::string null;
        int bag_num;

        line_stream >> c1 >> c2 >> null >> null;
        if (!line_stream.good()) {
            continue;
        }
        int parent_code = get_bag_code(c1, c2, bags_types);

        while (bags_inclusion.size() < bags_types.size()) {
            bags_inclusion.push_back({});
        }

        while (line_stream.good()) {
            line_stream >> bag_num >> c1 >> c2;
            if (line_stream.good()) {
                int child_code = get_bag_code(c1, c2, bags_types);
                bags_inclusion[parent_code].push_back({bag_num, child_code});
            }
            line_stream >> null;
        }

        while (bags_inclusion.size() < bags_types.size()) {
            bags_inclusion.push_back({});
        }
    }

    int n = bags_types.size();

    std::vector<std::vector<int>> parents(n);
    for (int parent = 0; parent < n; ++parent) {
        for (const auto& [_, child] : bags_inclusion[parent]) {
            parents[child].push_back(parent);
        }
    }

    std::vector<bool> visited(n, false);
    std::vector<uint64_t> total_bags(n, 0);

    std::function<void(int)> visit;
    visit = [&](int parent) {
        visited[parent] = true;

        uint64_t bags_sum = 0;
        for (const auto& [num, child] : bags_inclusion[parent]) {
            if (!visited[child]) {
                visit(child);
            }
            bags_sum += num * (total_bags[child] + 1);
        }
        total_bags[parent] = bags_sum;
    };

    for (int code = 0; code < n; ++code) {
        if (!visited[code]) {
            visit(code);
        }
    }

    int my_bag_code = bags_types["shiny gold"];
    std::cout << total_bags[my_bag_code] << std::endl;
}

