import re


def parse_expression(tokens):
    return parse_product(tokens)

def parse_product(tokens):
    assert len(tokens) > 0

    result, tokens = parse_sum(tokens)
    while len(tokens) > 0:
        if tokens[0] == '*':
            tokens.pop(0)
            rhs, tokens = parse_sum(tokens)
            result = result * rhs
        else:
            break

    return result, tokens

def parse_sum(tokens):
    assert len(tokens) > 0

    result, tokens = parse_unit(tokens)
    while len(tokens) > 0:
        if tokens[0] == '+':
            tokens.pop(0)
            rhs, tokens = parse_unit(tokens)
            result = result + rhs
        else:
            break

    return result, tokens

def parse_unit(tokens):
    assert len(tokens) > 0

    t = tokens.pop(0)
    if t == '(':
        result, tokens = parse_expression(tokens)
        assert tokens.pop(0) == ')'
        return result, tokens
    else:
        return int(t), tokens


sum = 0

try:
    while True:
        line = input()
        tokens = [t for word in re.split(r'(\d+)', line) for t in word]
        tokens = [t.strip() for t in tokens if len(t.strip()) > 0]
        if len(tokens) == 0:
            continue

        result, leftover = parse_expression(tokens)
        assert len(leftover) == 0

        sum += result

except EOFError:
    pass

print(sum)
