import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # Check if each file exists
    for command in sys.argv[1:]:
        try:
            file = open(command)
        except FileNotFoundError:
            sys.exit(f"File not found.\n{command} doesn't exist.")
        else:
            file.close()

    # Read database file into a variable
    database = dict()

    with open(sys.argv[1]) as fileDataBase:

        # Create Dict Reader
        reader = csv.DictReader(fileDataBase)

        # Store each sequence of data base
        STRs = list()
        for header in reader.fieldnames:
            if header == "name":
                pass
            else:
                STRs.append(header)

        # Iterate over each row, creating 'dict' to be stored in database
        for row in reader:

            # Save name
            name = row["name"]

            # Create 'dict' for each content and populate it
            content = list()
            for collum in reader.fieldnames:
                if collum == "name":
                    pass
                else:
                    content.append(tuple([collum, row[collum]]))

            # Append content into database
            database[name] = content

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as fileDNA:

        # Create reader
        reader = fileDNA.read()

        # Convert a one line .txt file into a list of characters
        sequence = list(reader)
        sequence.pop(-1)

    # TODO: Find longest match of each STR in DNA sequence
    STRsCount = list()
    for subsequence in STRs:
        STRsCount.append(longest_match(sequence, list(subsequence)))

    # Create STRs result list of tuples
    STRsResults = list(zip(STRs, STRsCount))

    # TODO: Check database for matching profiles
    result = find_match(database, STRsResults)

    print(result)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def find_match(database, STRsResults):

    # Iterate over database
    for entry, values in database.items():

        # Convert the values in the database to strings
        db_values = [str(value[1]) for value in values]

        # Convert the values in STRsResults to strings
        result_values = [str(result[1]) for result in STRsResults]

        # Compare the two lists of values
        if db_values == result_values:
            return entry

    return "No match"


main()
