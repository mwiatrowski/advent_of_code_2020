#include <iostream>
#include <string>
#include <vector>


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
    int time_start;
    std::cin >> time_start;

    std::string bus_ids;
    std::cin >> bus_ids;

    int earliest_id      = -1;
    int earliest_minutes = -1;

    for (const std::string& bus_id_str : split(bus_ids, ',')) {
        int bus_id;
        try {
            bus_id = std::stoi(bus_id_str);
        } catch(std::invalid_argument) {
            continue;
        }

        int minutes = (bus_id - (time_start % bus_id)) % bus_id;
        if (earliest_id == -1 || minutes < earliest_minutes) {
            earliest_id      = bus_id;
            earliest_minutes = minutes;
        }
    }

    std::cout << (earliest_id * earliest_minutes) << std::endl;
}
