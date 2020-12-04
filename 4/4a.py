REQUIRED_FIELDS = [
    'byr',
    'iyr',
    'eyr',
    'hgt',
    'hcl',
    'ecl',
    'pid',
]

lines = []
try:
    while True:
        lines.append(input().strip())
except EOFError:
    pass

line_groups = [[]]
for line in lines:
    if len(line) > 0:
        line_groups[-1].append(line)
    else:
        line_groups.append([])

passports = []
for line_group in line_groups:
    passport_string = ' '.join(line_group)
    fields = passport_string.split()
    passport = {}
    for field in fields:
        key, val = field.split(':')
        passport[key] = val
    passports.append(passport)

valid_passports = 0;
for passport in passports:
    for key in REQUIRED_FIELDS:
        if key not in passport:
            break
    else:
        valid_passports += 1

print(valid_passports)
