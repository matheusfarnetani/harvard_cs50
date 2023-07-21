def main():
    text = input("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    avg_letters = (letters / words) * 100
    avg_sentences = (sentences / words) * 100
    index = round((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_sentences(text):
    counter = 0
    for char in text:
        if char == '.' or char == '!' or char == '?':
            counter += 1

    return counter


def count_words(text):
    counter = 1
    for char in text:
        if char.isspace():
            counter += 1

    return counter


def count_letters(text):
    counter = 0
    for char in text:
        if char.isalpha():
            counter += 1

    return counter


if __name__ == "__main__":
    main()
