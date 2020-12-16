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


ticket_scanning_error_rate = 0
for ticket in nearby_tickets:
    for value in ticket:
        for interval in merged_intervals:
            if value >= interval[0] and value <= interval[1]:
                break
        else:
            ticket_scanning_error_rate += value

print(ticket_scanning_error_rate)
