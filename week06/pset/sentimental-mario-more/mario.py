def main():
    height = getSize()

    for i in range(1, height + 1):
        printSpace(height - i)
        printSymbol(i)

        print("  ", end="")

        printSymbol(i)
        print()


def getSize():
    while True:
        try:
            number = input("Height: ")
            number = int(number)
        except ValueError:
            continue
        
        if number >= 1 and number <= 8:
            return number


def printSymbol(size):
    print("#" * size, end="")


def printSpace(size):
    print(" " * size, end="")


if __name__ == "__main__":
    main()
