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


all_allergens = list(possible_ingredients.keys())
solution = { allergen: None for allergen in all_allergens }
def find_solution(allergens):
    global solution
    if len(allergens) == 0:
        return True

    allergen = allergens[0]
    for ingredient in possible_ingredients[allergen]:
        if ingredient in solution.values():
            continue
        solution[allergen] = ingredient
        if find_solution(allergens[1:]):
            return True
        solution[allergen] = None

    return False

find_solution(all_allergens)

print(','.join([ingredient for (allergen, ingredient) in sorted(solution.items())]))
