#include <array>
#include <iostream>
#include <string>
#include <vector>


const int N = 1000000;
const int MOVES = 10000000;


int main()
{
    std::vector<int> next(N);
    int first_cup;

    {
        std::string input;
        std::cin >> input;

        int previous_cup = -1;
        for (size_t i = 0; i < input.size(); ++i) {
            int cup = input[i] - '1';
            if (i == 0) {
                first_cup = cup;
            }
            if (previous_cup != -1) {
                next[previous_cup] = cup;
            }
            previous_cup = cup;
        }
        for (size_t i = input.size(); i < N; ++i) {
            next[previous_cup] = i;
            previous_cup = i;
        }
        next[N - 1] = first_cup;
    }

    int current = first_cup;

    for (int move = 0; move < MOVES; ++move) {
        int r1 = next[current];
        int r2 = next[r1];
        int r3 = next[r2];
        next[current] = next[r3];

        int destination = (current - 1 + N) % N;
        while (destination == r1 || destination == r2 || destination == r3) {
            destination = (destination - 1 + N) % N;
        }
        next[r3] = next[destination];
        next[destination] = r1;

        current = next[current];
    }

    uint64_t result_1 = next[0];
    uint64_t result_2 = next[result_1];
    std::cout << (result_1 + 1) * (result_2 + 1) << std::endl;
}
