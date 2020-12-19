rules = {}

def try_parse(rule, input):
    global rules

    rhs = rules[rule]
    if type(rhs) == str:
        if input.startswith(rhs):
            return [input[len(rhs):]]
        else:
            return []
    else:
        successful_parses = []

        for alternative in rhs:
            leftover_input = [input]
            for child_rule in alternative:
                new_leftover_input = []
                for suffix in leftover_input:
                    leftover = try_parse(child_rule, suffix)
                    new_leftover_input.extend(leftover)
                leftover_input = list(set(new_leftover_input))

            successful_parses.extend(leftover_input)
            successful_parses = list(set(successful_parses))

        return successful_parses


rules = {}

while True:
    line = input()
    if len(line) == 0:
        break
    lhs, rhs = line.split(':')
    id = int(lhs)
    rule_text = rhs.strip()

    if rule_text[0] == '"':
        rules[id] = rule_text.strip('"')
    else:
        if id == 8:
            alternatives = [[42], [42, 8]]
        elif id == 11:
            alternatives = [[42, 31], [42, 11, 31]]
        else:
            alternatives = []
            for alt in rule_text.split('|'):
                alternatives.append([int(x) for x in alt.split()])

        rules[id] = alternatives


matching_messages = 0

while True:
    try:
        msg = input()
    except EOFError:
        break

    leftover_input = try_parse(0, msg)

    if '' in leftover_input:
        matching_messages += 1

print(matching_messages)
