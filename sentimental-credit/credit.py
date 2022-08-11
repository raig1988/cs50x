# TODO

from cs50 import get_int

def main():
    credit_card_number = get_int("Number: ")
    checksum(credit_card_number)

def checksum(number):
    # variable initialization for EOD
    eod1_b = (number / 10) % 10
    eod1_bm = eod1_b * 2
    eod1_1 = eod1_bm % 10
    eod1_2 = (eod1_bm / 10) % 10
    eod1_r = eod1_1 + eod1_2
    # variable initialization for EOD 2
    eod2_b = (number / (pow(10, 3))) % 10
    eod2_bm = eod2_b * 2
    eod2_1 = eod2_bm % 10
    eod2_2 = (eod2_bm / 10) % 10
    eod2_r = eod2_1 + eod2_2
    # variable initialization for EOD 3
    eod3_b = (number / (pow(10, 5))) % 10
    eod3_bm = eod3_b * 2
    eod3_1 = eod3_bm % 10
    eod3_2 = (eod3_bm / 10) % 10
    eod3_r = eod3_1 + eod3_2
    # variable initialization for EOD 4
    eod4_b = (number / (pow(10, 7))) % 10
    eod4_bm = eod4_b * 2
    eod4_1 = eod4_bm % 10
    eod4_2 = (eod4_bm / 10) % 10
    eod4_r = eod4_1 + eod4_2
    # variable initialization for EOD 5
    eod5_b = (number / (pow(10, 9))) % 10
    eod5_bm = eod5_b * 2
    eod5_1 = eod5_bm % 10
    eod5_2 = (eod5_bm / 10) % 10
    eod5_r = eod5_1 + eod5_2
    # variable initialization for EOD 6
    eod6_b = (number / (pow(10, 11))) % 10
    eod6_bm = eod6_b * 2
    eod6_1 = eod6_bm % 10
    eod6_2 = (eod6_bm / 10) % 10
    eod6_r = eod6_1 + eod6_2
    # variable initialization for EOD 7
    eod7_b = (number / (pow(10, 13))) % 10
    eod7_bm = eod7_b * 2
    eod7_1 = eod7_bm % 10
    eod7_2 = (eod7_bm / 10) % 10
    eod7_r = eod7_1 + eod7_2
    # variable initialization for EOD 8
    eod8_b = (number / (pow(10, 15))) % 10
    eod8_bm = eod8_b * 2
    eod8_1 = eod8_bm % 10
    eod8_2 = (eod8_bm / 10) % 10
    eod8_r = eod8_1 + eod8_2
    # adding up everyother digit
    add_eod = eod1_r + eod2_r + eod3_r + eod4_r + eod5_r + eod6_r + eod7_r + eod8_r

    # variable initialization for other digit
    od1 = number % 10
    od2 = (number / (pow(10, 2))) % 10
    od3 = (number / (pow(10, 4))) % 10
    od4 = (number / (pow(10, 6))) % 10
    od5 = (number / (pow(10, 8))) % 10
    od6 = (number / (pow(10, 10))) % 10
    od7 = (number / (pow(10, 12))) % 10
    od8 = (number / (pow(10, 14))) % 10
    add_od = od1 + od2 + od3 + od4 + od5 + od6 + od7 + od8

    # adding up eod total and other digit total
    total = add_eod + add_od

    if (total % 10 == 0): # checks if card is valid
        if (number < 1000000000000000
            and number > 99999999999999): ## american express 15 digits - less than 16 digits and moree than 14 digits
            if (od8 == 3 and (eod7_b == 4 or eod7_b == 7)):
                print("AMEX")
            else:
                print("INVALID")
        if (number < 10000000000000000 and number > 999999999999999): # mastercard 16 digits - less than 17 and more than 15
            if (eod8_b == 5 and (od8 == 1 or od8 == 2 or od8 == 3 or od8 == 4 or od8 == 5)):
                print("MASTERCARD")
            else:
                print("INVALID")
        if (number < 10000000000000000 and number > 999999999999999): # visa 16 digits - less than 17 and more than 15
            if (eod8_b == 4):
                print("VISA")
        if (number < 10000000000000 and number > 999999999999): # visa 13 digits  - less than 14 and more than 12
            if (od7 == 4):
                print("VISA")
        if (number < 1000000000000): # less than 13 digits
            print("INVALID")
    elif (total % 10 != 0): # if total modulo 10 not zero, invalid
        print("INVALID")

main()