import re


rules = {}
dependency_count = {}
parent_rules = {}

while True:
    line = input()
    if len(line) == 0:
        break
    lhs, rhs = line.split(':')
    id = int(lhs)
    rule_text = rhs.strip()

    if id not in parent_rules:
        parent_rules[id] = set()

    if rule_text[0] == '"':
        rules[id] = rule_text.strip('"')
        dependency_count[id] = 0
    else:
        alternatives = []
        for alt in rule_text.split('|'):
            alternatives.append([int(x) for x in alt.split()])
        rules[id] = alternatives

        rule_dependencies = set([x for alt in alternatives for x in alt])
        dependency_count[id] = len(rule_dependencies)
        for child in rule_dependencies:
            if child not in parent_rules:
                parent_rules[child] = set()
            parent_rules[child].add(id)


rule_regexes = {}

rule_queue = []
for id, count in dependency_count.items():
    if count == 0:
        rule_queue.append(id)

while len(rule_queue) > 0:
    id = rule_queue.pop(0)

    rhs = rules[id]
    if type(rhs) == str:
        rule_regexes[id] = rhs
    else:
        regex = '(?:'
        for i, alternative in enumerate(rhs):
            if i != 0:
                regex += '|'
            regex += '(?:'
            for subrule in alternative:
                 regex += rule_regexes[subrule]
            regex += ')'
        regex += ')'
        rule_regexes[id] = regex

    for parent in parent_rules[id]:
        dependency_count[parent] -= 1
        if dependency_count[parent] == 0:
            rule_queue.append(parent)


root_rule_regex = re.compile(rule_regexes[0])
matching_messages = 0

while True:
    try:
        msg = input()
    except EOFError:
        break

    match_obj = root_rule_regex.match(msg)
    if match_obj is not None and match_obj.span() == (0, len(msg)):
        matching_messages += 1

print(matching_messages)
