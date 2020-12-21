import re
import sys


all_ingredients = {}
possible_ingredients = {}


for line in sys.stdin:
    ingredients, allergens = line.split('(')
    ingredients = ingredients.split()
    allergens = re.findall(r"(\w+)", allergens)[1:]

    for ingredient in ingredients:
        all_ingredients[ingredient] = all_ingredients.get(ingredient, 0) + 1

    for allergen in allergens:
        if allergen not in possible_ingredients:
            possible_ingredients[allergen] = set(ingredients)
        else:
            possible_ingredients[allergen] = possible_ingredients[allergen] & set(ingredients)

impossible_ingredients = set(all_ingredients.keys())
for allergen, ingredients in possible_ingredients.items():
    impossible_ingredients = impossible_ingredients - ingredients

result = 0
for ingredient in impossible_ingredients:
    result += all_ingredients[ingredient]
print(result)
