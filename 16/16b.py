ticket_fields = []
while True:
    line = input()
    if len(line) == 0:
        break

    name, constraints = line.split(':')
    intervals = [tuple((int(x) for x in range.split('-'))) for range in constraints.split('or')]

    ticket_fields.append((name, intervals))

input()
your_ticket = tuple((int(x) for x in input().split(',')))
input()

nearby_tickets = []
input()
try:
    while True:
        ticket_tokens = input().split(',')
        nearby_tickets.append(tuple((int(x) for x in ticket_tokens)))
except EOFError:
    pass


all_intervals = [interval for _, list_of_intervals in ticket_fields for interval in list_of_intervals]
all_intervals = sorted(all_intervals)
merged_intervals = []
for interval in all_intervals:
    if len(merged_intervals) == 0:
        merged_intervals.append(interval)
    else:
        last = merged_intervals[-1]
        if last[1] >= interval[0] - 1:
            merged_intervals[-1] = (last[0], interval[1])
        else:
            merged_intervals.append(interval)


valid_tickets = []
for ticket in nearby_tickets:
    ticket_invalid = False
    for value in ticket:
        for interval in merged_intervals:
            if value >= interval[0] and value <= interval[1]:
                break
        else:
            ticket_invalid = True
            break
    if not ticket_invalid:
        valid_tickets.append(ticket)


n = len(ticket_fields)

possible_names = [set(range(n)) for _ in range(n)]
for ticket in valid_tickets:
    for field, value in enumerate(ticket):
        impossible_names = set()
        for name in possible_names[field]:
            for interval in ticket_fields[name][1]:
                if value >= interval[0] and value <= interval[1]:
                    break
            else:
                impossible_names.add(name)
        possible_names[field] = possible_names[field] - impossible_names


match_graph = [set() for _ in range(2 * n)]
for field, names in enumerate(possible_names):
    for name in names:
        match_graph[field].add(name + n)

matches = [None for _ in range(2 * n)]

def find_match(field, visited):
    global match_graph
    global matches

    visited.add(field)

    for name in match_graph[field]:
        if name in visited:
            continue

        prev_match = matches[name]
        if prev_match is not None:
            visited.add(name)
            found_new_match = find_match(prev_match, visited)
            if not found_new_match:
                visited.remove(name)
                continue

        matches[field] = name
        matches[name] = field

        return True

    visited.remove(field)
    return False

for field in range(n):
    if matches[field] is None:
        find_match(field, set())


result = 1
for (name, _), field_id in zip(ticket_fields, matches[n:]):
    if name.startswith('departure'):
        result *= your_ticket[field_id]

print(result)
