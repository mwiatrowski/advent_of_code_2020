#include <iostream>
#include <sstream>
#include <string>
#include <vector>


enum class Opcode {
    Nop,
    Acc,
    Jmp,
};

struct Op {
    Opcode opcode;
    int argument;
};


std::vector<Op> load_program()
{
    std::vector<Op> program;

    std::string cmd;
    int arg;
    while (!std::cin.eof()) {
        std::cin >> cmd >> arg;
        if (std::cin.fail()) {
            break;
        }

        if (cmd == "nop") {
            program.push_back({Opcode::Nop, 0});
        } else if (cmd == "acc") {
            program.push_back({Opcode::Acc, arg});
        } else if (cmd == "jmp") {
            program.push_back({Opcode::Jmp, arg});
        }
    }

    return program;
}


int main()
{
    std::vector<Op> program = load_program();

    int64_t accumulator = 0;
    size_t program_counter = 0;

    std::vector<bool> executed(program.size(), false);

    while (true) {
        if (executed[program_counter]) {
            break;
        }
        executed[program_counter] = true;

        const Op& op = program[program_counter];
        switch (op.opcode) {
        case Opcode::Nop:
            program_counter += 1;
            break;
        case Opcode::Acc:
            accumulator += op.argument;
            program_counter += 1;
            break;
        case Opcode::Jmp:
            program_counter += op.argument;
            break;
        }
    }

    std::cout << accumulator << std::endl;
}
