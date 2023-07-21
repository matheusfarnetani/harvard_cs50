def main():
    number = int(input("Number: "))
    
    if checkSum(number):
        card = defineCard(number)
    else:
        card = "INVALID"

    print(card)


def checkSum(number):
    numDigits = len(str(number))
    digitArray = [int(digit) for digit in str(number)]

    cardsum = 0

    for i in range(numDigits - 2, -1, -2):
        a = digitArray[i] * 2

        while a != 0:
            cardsum += a % 10
            a //= 10

    for i in range(numDigits - 1, -1, -2):
        cardsum += digitArray[i]

    return cardsum % 10 == 0


def defineCard(number):
    numDigits = len(str(number))
    firstDigit = number // 10 ** (numDigits - 1)
    firstTwoDigits = number // 10 ** (numDigits - 2)

    if numDigits == 15:
        if firstTwoDigits == 34 or firstTwoDigits == 37:
            return "AMEX"
    elif numDigits == 16:
        if 51 <= firstTwoDigits <= 55:
            return "MASTERCARD"
        elif firstDigit == 4:
            return "VISA"
    elif numDigits == 13:
        if firstDigit == 4:
            return "VISA"

    return "INVALID"


if __name__ == "__main__":
    main()
