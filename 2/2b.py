import re

re_entry = re.compile(r'((?:[0-9]+))-((?:[0-9]+))\s(\S)\:\s(\S*)')

valid_passwords = 0

try:
    while True:
        entry = input()
        match = re_entry.match(entry)
        p1, p2, c, password = list(match.groups())

        p1_ok = password[int(p1) - 1] == c
        p2_ok = password[int(p2) - 1] == c
        if p1_ok != p2_ok:
            valid_passwords += 1
except EOFError:
    pass

print(valid_passwords)
