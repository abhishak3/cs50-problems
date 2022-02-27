def main():
    # getting user card number
    card_number = int(input("Number: "))

    copy = card_number

    # length of card_number
    count = 0
    while (copy):
        copy //= 10
        count += 1

    # validating length of card number
    if (count < 13):
        print("INVALID")
        return 0

    copy = card_number

    # alternate sum
    sum = 0
    while (copy):
        copy //= 10
        if ((copy % 10) * 2 < 10):
            sum += (copy % 10) * 2
        else:
            sum += ((copy % 10) * 2) % 10 + 1
        copy //= 10

    copy = card_number

    # final sum
    newsum = 0
    while (copy):
        newsum += copy % 10
        copy //= 10
        copy //= 10

    newsum += sum

    # determining card type
    if (newsum % 10 == 0):
        number = int(str(card_number)[0:2])
        if (number >= 40 and number <= 49):
            print("VISA")
        elif (number == 34 or number == 37):
            print("AMEX")
        elif (number >= 51 and number <= 55):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


# execute the main function
if __name__ == "__main__":
    main()
