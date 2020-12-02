import re

re_entry = re.compile(r'((?:[0-9]+))-((?:[0-9]+))\s(\S)\:\s(\S*)')

valid_passwords = 0

try:
    while True:
        entry = input()
        match = re_entry.match(entry)
        c_min, c_max, c, password = list(match.groups())

        c_count = password.count(c)
        if int(c_min) <= c_count and c_count <= int(c_max):
            valid_passwords += 1
except EOFError:
    pass

print(valid_passwords)
