# TODO
from cs50 import get_int
# like a do while loop
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break
# if its not within this constraints, it breaks

for i in range(height):
    for k in range(height - i - 1): 
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()
