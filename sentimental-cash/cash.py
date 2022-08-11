# TODO
from cs50 import get_float
import math
import decimal

# only coins availables quarters 0.25, dimes 0.1, nickels 0.05 and pennies 0.01


def main():
    cents = get_cents()

    floor_quarters = cents // 0.25  # finding Floor Quarters
    remainder_quarters = cents % 0.25  # finding Modulo Quarters
    round_quarters = round(remainder_quarters, 2)

    floor_dimes = round_quarters // 0.1  # finding Floor Dimes
    remainder_dimes = round_quarters % 0.1  # finding Modulo Dimes
    round_dimes = round(remainder_dimes, 2)

    floor_nickels = round_dimes // 0.05  # finding Floor Nickels
    remainder_nickels = round_dimes % 0.05   # finding Modulo Nickels
    round_nickels = round(remainder_nickels, 2)

    floor_pennies = round_nickels // 0.01  # finding Floor Pennies
    remainder_pennies = round_nickels % 0.01  # finding Modulo Pennies
    round_pennies = round(remainder_pennies, 2)

    coins = floor_quarters + floor_dimes + floor_nickels + floor_pennies
    round_coins = round(coins)
    print(f"{round_coins}")  # prints rounded coins

# function to obtain cents


def get_cents():
    while True:
        n = get_float("Change owed: ")
        if n > 0:
            return n
        else:
            print("Format: 9.0")


main()
