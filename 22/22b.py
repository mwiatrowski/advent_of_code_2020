import sys


decks = []

while True:
    try:
        player = input()
        deck = []
        while True:
            try:
                card_str = input()
                if len(card_str) == 0:
                    break
                deck.append(int(card_str))
            except EOFError:
                break
        decks.append(deck)
    except EOFError:
        break


def game(deck0, deck1):
    states = set()

    while len(deck0) > 0 and len(deck1) > 0:
        state = (str(deck0), str(deck1))
        if state in states:
            return 0, deck0
        states.add(state)

        card0 = deck0.pop(0)
        card1 = deck1.pop(0)

        if card0 <= len(deck0) and card1 <= len(deck1):
            subdeck0 = deck0[:card0]
            subdeck1 = deck1[:card1]
            winner, _ = game(subdeck0, subdeck1)
        else:
            winner = 0 if card0 > card1 else 1

        if winner == 0:
            deck0.extend([card0, card1])
        else:
            deck1.extend([card1, card0])

    if len(deck1) == 0:
        return 0, deck0
    else:
        return 1, deck1


_, winner_deck = game(decks[0], decks[1])

score = 0
for i, card in enumerate(winner_deck):
    score += (len(winner_deck) - i) * card
print(score)
