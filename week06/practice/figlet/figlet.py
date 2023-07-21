from sys import argv, exit
from pyfiglet import Figlet
from random import choice


def main():
    
    figlet = Figlet()
    fonts = figlet.getFonts()
        
    if len(argv) == 1:
        font = "random"
    elif len(argv) == 2:
        usageMensage()
        exit(1)
    elif len(argv) == 3:
        if argv[1] == "-f" or argv[1] == "--font":
            if argv[2] in fonts:
                font = argv[2]
            else:
                exit(2)
        else:
            usageMensage()
            exit(1)

    text = input("Input: ")

    if font == "random":
        font = choice(fonts)
    
    figlet.setFont(font=font)

    print(figlet.renderText(text))


def usageMensage():
    print("Usage: python figlet.py")
    print("or   : python figlet.py --font [name of font]")
    print("or   : python figlet.py -f [name of font]")


if __name__ == "__main__":
    main()