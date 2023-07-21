import string


def main():
    greeting = input("Greeting: ")
    value = checkGreeting(greeting.lower())
    print(f"${value}")


def checkGreeting(greeting):
    # Removing punctuations
    words = greeting.translate(str.maketrans(",", " ", string.punctuation))

    # Creating list with words inputed
    words = words.split()

    if words[0] in ["hello"]:
        return 0
    elif words[0][0] == "h":
        return 20
    else:
        return 100

if __name__ == "__main__":
    main()
