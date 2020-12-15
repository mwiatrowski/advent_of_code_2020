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
    std::string input_line;
    std::getline(std::cin, input_line);

    std::vector<int> last_occurence(30000000, -1);
    int index = 0;
    int last_number = -1;

    for (const std::string& token : split(input_line, ',')) {
        if (index > 0) {
            last_occurence[last_number] = index - 1;
        }
        last_number = std::stoi(token);
        index += 1;
    }

    for ( ; index < 30000000; ++index) {
        int number;
        if (last_occurence[last_number] == -1) {
            number = 0;
        } else {
            number = index - 1 - last_occurence[last_number];
        }
        last_occurence[last_number] = index - 1;
        last_number = number;
    }

    std::cout << last_number << std::endl;
}
