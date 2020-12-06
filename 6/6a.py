groups = []

continue_parsing = True
while continue_parsing:
    group = ""
    try:
        while True:
            line = input()
            if len(line) == 0:
                break
            group += line.strip()
    except EOFError:
        continue_parsing = False
    groups.append(group)

result = 0
for group in groups:
    questions = set(group)
    result += len(questions)

print(result)
