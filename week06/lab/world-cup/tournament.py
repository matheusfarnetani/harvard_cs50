# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")
    
    # Save file dir
    file = sys.argv[1]
    
    # Create and populate teams list of dicts
    teams = []    
    teams = loadTeams(file)
    if teams[0] == False:
        sys.exit("File not found")
    print(teams)

    # Create and populate counts dicts of winner's count
    counts = {}
    for item in teams:
        counts[item["team"]] = 0
    print(counts)

    counter = 0
    while counter < N:
        winner = simulate_tournament(teams)

        # Update counts dict
        counts[winner] += 1    

        # Update counter of simulations       
        counter += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def loadTeams(file):
    """Loads team's file. Returns teams list, otherwise false"""

    # Create teams list to be returned
    teams = []

    try:
        # try opening file
        f = open(file)
        reader = csv.DictReader(f)
    except FileNotFoundError:
        # File not found, return param for exit
        teams = [False]
        return teams
    else:
        # Create dict for each team
        for row in reader:
            team = dict()
            team["team"] = row["team"]
            team["rating"] = int(row["rating"])

            # append to teams list
            teams.append(team)
    finally:
        # close file
        f.close()

    return teams


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    players = teams

    # 4 Rounds
    for round in range(4):
        players = simulate_round(players)

    return players[0]["team"]


if __name__ == "__main__":
    main()
