# syntax examples

# Conditional
letters_only = True if input().isalpha() else False


# List comprehension
num = [x for x in range(500)]


# Insert value into list
nums = [1, 2, 3, 4]
# Ways of doing it
nums.append(5)
nums.insert(4, 5) # Insert 5 into fourth position
nums[len(nums):] = [5]


# tuples
# List of tuples
presidents = [
    ("George Washington", 1789),
    ("John Adams", 1797),
    ("Thomas Jefferson", 1801),
    ("James Madison", 1809),
]
# Iterate and print over list of tuples
for prez, year in presidents:
    print("In {1}, {0}, took office".fomat(prez, year))


# Dictionaries
pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12,
}
# working with
pizzas["cheese"] = 8 # Updated value
if pizzas["vegetables"] < 12:
    # do something
    print(pizzas)
pizzas["bacon"] = 14 # append value


# loops
# The for loop in Python is extremely flexible
for pie in pizzas:
    print(pie)
for pie, price in pizzas.items(): # .items() transform dict into list and that could result in losing the order
    print(price)
    print("A whole {} pizza costs ${}".format(pie, price))


# functions
# All functions are introduced with the 'def' keyword.
#     also, no need for main; the interpreter reads from top to bottom!
#     if you wish to define 'main' nonetheless (and you might want to!), you
#     must at the very end of your code have:
if __name__ == "__main__":
    main()


# objects oriented programming
    # C structures contain a number of fields, wich we might also call 'properties'
        # but the 'properties' themselves can not ever stand on ther own
   
    # objects, meanwhile, have properties but also methods, or functions
    # that are inherent to the object, and mean nothing outside of it. You
    # define the methods inside the object also.
        # Thus, properties and methods don't ever stand on ther own

object.method() # how you call the method of the object

    # You define a type of object using the class keyword in Python
    
    # Classes require an initialization function, also more-generally known
    # as a 'constructor', wich sets the starting values of the properties
    # of the object

    # In defining each method of an object, self should be its first
    # parameter, wich stipulates on what object the method is called

class Student():

    def __init__(self, name, id):
        self.name = name
        self.id = id
    

    def changeID(self, id):
        self.id = id
    

    def print(self):
        print("{} - {}".format(self.name, self.id))

jane = Student("Jane", 10)
jane.print()
jane.changeID(11)
jane.print()

# To run your Python program through the Python interpreter at the 
# command-line, simple type

        # python <file>

# and your programim will run through the interpreter, which will
# execute everything inside of the file, top to bottom.

# You can also make your programs look a lot more like C programs
# when they execute by adding a shebang to the top of your Python files,
# which automatically finds and executes the interpreter for you

        #!/usr/bin/env python3

# If you do this, you need to change the permissions on your file
# as well using the Linux command chmod as follows:

        # chmod a+x <file>
    
# doing this you can execute the code with './yourprogram.py'