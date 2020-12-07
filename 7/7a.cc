#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <queue>


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

    int my_bag_code = bags_types["shiny gold"];

    std::vector<bool> valid_bags(n, false);
    std::queue<int> bfs_queue;
    bfs_queue.push(my_bag_code);

    while (!bfs_queue.empty()) {
        int code = bfs_queue.front();
        bfs_queue.pop();

        for (int parent : parents[code]) {
            if (!valid_bags[parent] && parent != my_bag_code) {
                valid_bags[parent] = true;
                bfs_queue.push(parent);
            }
        }
    }

    int valid_bags_count = 0;
    for (bool is_valid : valid_bags) {
        if (is_valid) {
            valid_bags_count += 1;
        }
    }

    std::cout << valid_bags_count << std::endl;
}

