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
    try:
        byr = int(passport['byr'])
        if len(passport['byr']) != 4 or byr < 1920 or byr > 2002:
            raise AssertionError

        iyr = int(passport['iyr'])
        if len(passport['iyr']) != 4 or iyr < 2010 or iyr > 2020:
            raise AssertionError

        eyr = int(passport['eyr'])
        if len(passport['eyr']) != 4 or eyr < 2020 or eyr > 2030:
            raise AssertionError

        hgt_val, hgt_un = passport['hgt'][:-2], passport['hgt'][-2:]
        hgt_val = int(hgt_val)
        if hgt_un == 'cm':
            if hgt_val < 150 or hgt_val > 193:
                raise AssertionError
        elif hgt_un == 'in':
            if hgt_val < 59 or hgt_val > 76:
                raise AssertionError
        else:
            raise AssertionError

        hcl = passport['hcl'][1:]
        if passport['hcl'][0] != '#':
            raise AssertionError
        if len(hcl) != 6:
            raise AssertionError
        for c in hcl:
            if c not in '0123456789abcdef':
                raise AssertionError

        ecl = passport['ecl']
        if ecl not in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']:
            raise AssertionError

        pid = passport['pid']
        if len(pid) != 9:
            raise AssertionError
        pid = int(pid)

        valid_passports += 1

    except KeyError:
        continue
    except ValueError:
        continue
    except AssertionError:
        continue

print(valid_passports)
