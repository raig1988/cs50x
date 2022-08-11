import sys
import csv

def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            teams[row[0]]=row[1:]


main()