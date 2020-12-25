#include <iostream>


uint64_t N = 20201227;


uint64_t find_loop_size(uint64_t public_key)
{
    uint64_t value = 1;
    uint64_t loop_size = 0;
    while (true) {
        if (value == public_key) {
            return loop_size;
        }
        value = (value * 7) % N;
        loop_size += 1;
    }
}


int main()
{
    uint64_t pk1, pk2;
    std::cin >> pk1 >> pk2;

    int m1 = find_loop_size(pk1);
    int m2 = find_loop_size(pk2);

    uint64_t result = 1;
    for (uint64_t i = 0; i < m1; ++i) {
        result = (result * pk2) % N;
    }

    std::cout << result << std::endl;
}