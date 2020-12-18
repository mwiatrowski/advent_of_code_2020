import re


sum = 0

try:
    while True:
        line = input()
        tokens = [t for word in re.split(r'(\d+)', line) for t in word]
        tokens = [t.strip() for t in tokens if len(t.strip()) > 0]
        if len(tokens) == 0:
            continue

        stack = []
        for token in tokens:
            if token in ['+', '*', '(', ')']:
                stack.append(token)
            else:
                val = int(token)
                stack.append(val)

            while len(stack) >= 3:
                t1 = stack[-3]
                t2 = stack[-2]
                t3 = stack[-1]

                if type(t1) == int and t2 in ['+', '*'] and type(t3) == int:
                    stack.pop()
                    stack.pop()
                    stack.pop()
                    stack.append({
                        '+': t1 + t3,
                        '*': t1 * t3,
                    }[t2])
                elif t1 == '(' and type(t2) == int and t3 == ')':
                    stack.pop()
                    stack.pop()
                    stack.pop()
                    stack.append(t2)
                else:
                    break

        result, = stack
        sum += result

except EOFError:
    pass

print(sum)
