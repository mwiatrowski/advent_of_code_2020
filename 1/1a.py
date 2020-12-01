entries = [False] * 2021
while True:
    x = int(input())
    if entries[2020 - x]:
        print(x * (2020 - x))
        break
    entries[x] = True
