from cs50 import SQL
from flask import Flask, render_template, request
from helpers import random_string
import random

app = Flask(__name__)

db = SQL("sqlite:///history.db")

app.config["TEMPLATES_AUTO_RELOAD"] = True

@app.route("/", methods=['GET', 'POST'])
def index():
    if request.method == "POST":

        # Get user's input from form in index.html
        page = request.form.get("page")

        # Try to convert user's input to integer
        try:
            page = int(page)
        except ValueError:
            return render_template("index.html", random_string="Enter a number!")
        
        # Check if it's a positive number
        if page < 0:
            return render_template("index.html", random_string="Type in a positive number!")
        
        # Add into database user's input
        db.execute("INSERT INTO history (page) VALUES (?);", page)

        # Set seed to be user's input
        random.seed(page)

    # Generate random text
    string = random_string(1000)

    # Get history from database
    rows = db.execute("SELECT * FROM history;")

    return render_template("index.html", random_string=string, history=rows)