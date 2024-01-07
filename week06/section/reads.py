import csv

books = []

# Add books to your shelf by reading from books.csv
with open("book.csv") as file:
    file_reader = csv.DictReader(file)
    for book in file_reader:
        books.append(book)
    
    # for row in file_reader:
    #     print(row[0])

# Print titles of books
for book in books:
    print(book["title"])