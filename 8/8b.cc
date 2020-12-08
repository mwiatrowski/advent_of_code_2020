#include <functional>
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
            program.push_back({Opcode::Nop, arg});
        } else if (cmd == "acc") {
            program.push_back({Opcode::Acc, arg});
        } else if (cmd == "jmp") {
            program.push_back({Opcode::Jmp, arg});
        }
    }

    return program;
}


int acc_change(const Op& op) {
    if (op.opcode == Opcode::Acc) {
        return op.argument;
    } else {
        return 0;
    }
}


int pc_change(const Op& op) {
    if (op.opcode == Opcode::Jmp) {
        return op.argument;
    } else {
        return 1;
    }
}


Op swap_opcode(Op op) {
    if (op.opcode == Opcode::Jmp) {
        op.opcode = Opcode::Nop;
    } else if (op.opcode == Opcode::Nop) {
        op.opcode = Opcode::Jmp;
    }
    return op;
}


void fix_program(std::vector<Op>& program)
{
    std::vector<bool> is_reachable(program.size(), false);
    std::vector<bool> can_reach_end(program.size(), false);

    {
        is_reachable[0] = true;
        size_t pc = 0;
        while (true) {
            size_t next_pc = pc + pc_change(program[pc]);
            if (next_pc == program.size() || is_reachable[next_pc]) {
                break;
            }
            is_reachable[next_pc] = true;
            pc = next_pc;
        }
    }

    {
        std::vector<bool> visited(program.size(), false);
        std::function<bool(size_t)> check_can_reach_end;
        check_can_reach_end = [&](size_t pc) -> bool {
            if (visited[pc]) {
                return can_reach_end[pc];
            }
            visited[pc] = true;

            size_t next_pc = pc + pc_change(program[pc]);
            if (next_pc == program.size()) {
                can_reach_end[pc] = true;
            } else {
                can_reach_end[pc] = check_can_reach_end(next_pc);
            }
            return can_reach_end[pc];
        };
        for (size_t pc = 0; pc < program.size(); ++pc) {
            check_can_reach_end(pc);
        }
    }

    for (size_t pc = 0; pc < program.size(); ++pc) {
        Op swapped_op = swap_opcode(program[pc]);
        size_t next_if_swapped = pc + pc_change(swapped_op);
        if (is_reachable[pc] && can_reach_end[next_if_swapped]) {
            program[pc] = swap_opcode(program[pc]);
            return;
        }
    }
}


int main()
{
    std::vector<Op> program = load_program();

    fix_program(program);

    int64_t accumulator = 0;
    size_t program_counter = 0;

    std::vector<bool> executed(program.size(), false);

    while (program_counter < program.size()) {
        if (executed[program_counter]) {
            break;
        }
        executed[program_counter] = true;

        const Op& op = program[program_counter];
        program_counter += pc_change(op);
        accumulator += acc_change(op);
    }

    std::cout << accumulator << std::endl;
}
