import csv
import sqlite3
import sys

def main():

    # Check command usage
    if len(sys.argv) != 3:
        print("usage python schema.py [.db] [.csv]")
        sys.exit(1)

    # Check if each file exists
    for command in sys.argv[1:]:
        try:
            file = open(command)
        except FileNotFoundError:
            sys.exit(f"File not found.\n{command} doesn't exist.")
        else:
            file.close()

    # Save path of each file
    dir_database = sys.argv[1]
    dir_csv = sys.argv[2]

    # Create necessary variables
    table_students = list()
    table_houses = list()
    table_assignments = list()
    control_houses = dict()

    # Open csv and save it content into dict
    with open(dir_csv) as filecsv:
        reader = csv.DictReader(filecsv)
        for row in reader:

            # Append new dict of student into list 'table_students'
            table_students.append({"id": int(row["id"]), "name": row["student_name"]})

            # Append simultaneously into  'table_house' and 'table_assignments'
            try:
                # Check if house has already been add to control
                # If it has return id
                house_id = control_houses[row["house"]]
            except KeyError:
                # If it hasn't add it
                control_houses[row["house"]] = len(control_houses) + 1

                # Get id
                house_id = control_houses[row["house"]]

                # Append into 'table_houses' dict
                table_houses.append({"id": house_id, "house": row["house"], "head": row["head"]})
            finally:
                # Anyway house_id exists
                # Append relation of student and house into 'table_assignments'
                table_assignments.append({"student_id": int(row["id"]), "house_id": house_id})

    # Create connection with database
    con = sqlite3.connect(dir_database)

    # Create cursor 
    cur = con.cursor()

    # Insert students into database
    # for student in table_students:
    #     cur.execute('INSERT INTO students (id, student_name) VALUES (?, ?)', (student["id"], student["name"]))
    
    # Insert houses into database
    for house in table_houses:
        cur.execute('INSERT INTO houses (id, house, head) VALUES (?, ?, ?)', (house["id"], house["house"], house["head"]))

    # Insert students into database
    for assignment in table_assignments:
        cur.execute('INSERT INTO assignments (student_id, house_id) VALUES (?, ?)', (assignment["student_id"], assignment["house_id"]))
    
    # Commit the changes
    con.commit()

    # Close the connection
    con.close()

    # Exits
    sys.exit(0)

main()