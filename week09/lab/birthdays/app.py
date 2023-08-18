import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Create secret key
app.secret_key = '123test'


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    # Everytime that the page is loaded it must get data from db
    birthdays = db.execute("SELECT * FROM birthdays")

    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # Validate name
        name = request.form.get("name")
        if not name:
            return render_template("index.html", error_message="Name cannot be empty", birthdays=birthdays)

        # Process dates returned from jQuery and Input
        selected_date = request.form.get("selected_date")
        selected_date = selected_date.split('/')

        # Date format returned is MM-DD-YYYY
        month = int(selected_date[0])
        day = int(selected_date[1])

        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html

        return render_template("index.html", birthdays=birthdays)


@app.route("/edit/<int:id>", methods=['GET', 'POST'])
def edit(id):

    # Get data from db
    db_data_return = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
    birthday = db_data_return[0]

    # If user is updating
    if request.method == "POST":

        # Get new name, if there isn't a new name use the old name
        new_name = request.form.get("new-name")
        if not new_name:
            new_name = birthday["name"]

        # Process dates returned from jQuery and Input
        new_selected_date = request.form.get("new_selected_date")
        if not new_selected_date:

            # If nothing is returned
            new_month = birthday["month"]
            new_day = birthday["day"]

        else:

            # Split list response
            new_selected_date = new_selected_date.split('/')

            # Date format returned is MM-DD-YYYY
            new_month = int(new_selected_date[0])
            new_day = int(new_selected_date[1])

        # Update db
        db.execute("UPDATE birthdays SET name = (?), month = (?), day = (?) WHERE id = (?)",
                   new_name, new_month, new_day, birthday["id"])

        # return to home page
        return redirect("/")

    return render_template("edit.html", id=birthday["id"], name=birthday["name"], month=birthday["month"], day=birthday["day"])


@app.route("/delete/<int:id>", methods=["GET", "POST"])
def delete(id):

    # Get data from db
    db_data_return = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
    birthday = db_data_return[0]

    # Delete entry by id from the database and redirect back to the display page
    return render_template("delete.html", id=birthday["id"], name=birthday["name"], month=birthday["month"], day=birthday["day"])


@app.route("/delete/<int:id>/confirm", methods=["POST"])
def delete_confirm(id):

    # Delete data from database
    db.execute("DELETE FROM birthdays WHERE id = (?)", id)

    return redirect("/")


@app.route("/delete/cancel", methods=["POST"])
def delete_cancel():
    return redirect("/")
