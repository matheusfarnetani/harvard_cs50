from sys import argv, exit

# order -> main
# prompt items (one per line) until ctrl + d -> input
# display total cost $0.00 -> calculate

# user's input case insensitively (titlecased)


def main():
    # argv
    if len(argv) == 1:
        pass

    # control variables
    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }
    bill = 0
    order = list()

    while True:
        try:
            # prompt
            order += prompt(menu)
            
            # calculate
            bill = calculate(order, menu)

            # display
            display(bill)
        except EOFError:
            exit(0)    


def prompt(menu):
    # get user input
    # return list

    orders = list()
    while True:
        order = input("Item: ").title()
        for item in menu:
            if order == item:
                orders.append(order)
                return orders


def calculate(order, menu):
    # get value by list
    # return total

    sum = 0
    for item in order:
        sum += float(menu[item])
    
    return sum


def display(bill):
    # just print something
    print(f"Total: ${bill:.2f}")


if __name__ == "__main__":
    main()