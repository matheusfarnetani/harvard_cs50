import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()
    for row in reader:
        try:
            if len(new_cases[row["state"]]) < 14:
                new_cases[row["state"]].append(int(row["cases"]) - previous_cases[row["state"]])             
            elif len(new_cases[row["state"]]) == 14:
                new_cases[row["state"]].pop(0)
                new_cases[row["state"]].append(int(row["cases"]) - previous_cases[row["state"]])
        except KeyError:
            new_cases[row["state"]] = list()
            previous_cases[row["state"]] = 0
        else:
            previous_cases[row["state"]] = int(row["cases"])
    
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        try:
            averagePast = sum(new_cases[state][0:7]) / 7
            averageRecent = sum(new_cases[state][7:]) / 7
        except ZeroDivisionError:
            averagePast = 0
            averageRecent = 0
        else:
            increase = ((averageRecent - averagePast) / averagePast) * 100
            print(f"{state} had a 7-day average of {int(averageRecent)} and an increase of {int(increase)}%.")
            

main()
