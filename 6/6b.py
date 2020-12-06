groups = []

continue_parsing = True
while continue_parsing:
    group = None
    try:
        while True:
            line = input()
            if len(line) == 0:
                break
            if group is None:
                group = set(line)
            else:
                group = group & set(line)
    except EOFError:
        continue_parsing = False
    groups.append(group)

result = 0
for group in groups:
    result += len(group)

print(result)
