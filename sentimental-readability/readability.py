# TODO

from cs50 import get_string


# main program printing grades includes asking input from user and 3 different type of responses
def main():
    text = get_string("Text: ")
    countletters = count_letters(text)
    countwords = count_words(text)
    countsentences = count_sentences(text)
    index = formulacalc(countletters, countwords, countsentences)
    round_index = round(index)

    # conditions for every output shown
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round_index}")


# function that counts each letter in the array if its alphabetic
def count_letters(text):
    countletters = 0
    for letter in text:
        if (letter.isalpha()):
            countletters += 1
    return countletters


# function that counts each word in the array by counting spaces and adding 1 at the end.
def count_words(text):
    countwords = 0
    for letter in text:
        if (letter.isspace()):
            countwords += 1
    return countwords + 1


# function that counts sentences if they end on dot, exclamation or interrogration
def count_sentences(text):
    countsentences = 0
    for letter in text:
        if letter == '.' or letter == '!' or letter == '?':
            countsentences += 1
    return countsentences


# formula that calculates index by data type float casting int data types
def formulacalc(countletters, countwords, countsentences):
    L = (countletters / countwords) * 100
    S = (countsentences / countwords) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8
    return index


main()
