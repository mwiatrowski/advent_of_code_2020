import re
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


while all(len(deck) > 0 for deck in decks):
    cards = []
    for i, deck in enumerate(decks):
        cards.append((deck.pop(0), i))
    cards = sorted(cards, reverse=True)
    _, winner = cards[0]
    decks[winner].extend(card for (card, i) in cards)


winner_deck = decks[0] + decks[1]
score = 0
for i, card in enumerate(winner_deck):
    score += (len(winner_deck) - i) * card
print(score)
