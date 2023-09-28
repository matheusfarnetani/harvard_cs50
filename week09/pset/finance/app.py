import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, check_password

# Configure application
app = Flask(__name__)

# Secret key
app.secret_key = "debug123"

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Retrieve row from database where the user has data
    user_info = db.execute(
        "SELECT * FROM users WHERE id = (?)", session.get("user_id"))[0]

    # Retrieve all shares related to user
    raw_user_stocks = db.execute(
        "SELECT stock_name, SUM(total_shares) AS total_shares FROM stock_transactions WHERE user_id = ? GROUP BY stock_name;",
        session.get("user_id"))

    # Filter data
    user_stocks = [
        stock for stock in raw_user_stocks if stock["total_shares"] != 0]

    responses = []
    totals = []

    # Get currently total value for each stock and individual stock value
    for stock in user_stocks:
        response = lookup(stock["stock_name"])
        if response is not None:
            responses.append(response)
            total = response["price"] * stock["total_shares"]
            totals.append(total)
        else:
            responses.append("Failed to load.")

    # The term might be incorret, but calculated user's liquid balance
    user_liquid = sum(totals) + user_info["cash"]

    # Zip all data for rendering
    table_data = zip(user_stocks, responses, totals)

    return render_template("index.html", username=user_info["username"], cash=user_info["cash"], table_data=table_data, liquid=user_liquid)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Get user's cash everytime the page is loaded
    user_cash = db.execute(
        "SELECT cash FROM users WHERE id = (?)", session.get("user_id"))[0]["cash"]

    # Get parameters. Jinja will handle correct rendering
    symbol = request.args.get("symbol")

    if request.method == "POST":

        # Get and ensure that user inputed a symbol
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Please provide a stock symbol.", 400)

        # Get and ensure that user inputed a share
        shares = request.form.get("shares")
        if not shares:
            return apology("Please provida a quantity of shares.", 400)

        # Convert shares to int
        try:
            shares = int(shares)
        except ValueError:
            return apology("The quantity of shares must be a integer.", 400)

        # Check if shares is a positive number
        if shares <= 0:
            return apology("Number of shares must be greater than 0.", 400)

        # Get stock's info from API
        response = lookup(symbol)
        if not response:
            return apology("No results where found for this stock symbol.", 400)

        # Perform calculations
        price = response["price"]
        total = shares * price

        # Check if user's cash is enough to buy
        if total > user_cash:
            flash(
                f"You don't have enough money. The total of your purchase was ${total}.")
            return redirect("/buy")

        # Perfom calculation
        new_user_cash = user_cash - total

        # Set transaction type
        transaction_type = "BUY"

        # Insert the purchase data into the stock_transactions table
        db.execute("INSERT INTO stock_transactions (user_id, type, stock_name, total_shares, share_value, transaction_value, transaction_date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session.get("user_id"), transaction_type, symbol, shares, price, total, datetime.now())

        # Update user's cash in db
        db.execute("UPDATE users SET cash = (?) WHERE id = (?)",
                   new_user_cash, session.get("user_id"))

        return redirect("/")

    return render_template("buy.html", user_cash=user_cash, symbol=symbol)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():

    if request.method == "POST":

        # Check if user has inputed a value
        add_cash = request.form.get("add-cash")
        if not add_cash:
            flash("Please provide a value to add.")
            return redirect("/cash")

        # Convert cash to float
        try:
            add_cash = float(add_cash)
        except ValueError:
            flash("The value must be a number.")
            return redirect("/cash")

        # Check if cash is a positive number
        if add_cash <= 0:
            flash("Cash value must be greater than 0")
            return redirect("/cash")

        # Check if user has inputed password
        password = request.form.get("confirm-password")
        if not password:
            flash("Please provide your password")
            return redirect("/cash")

        # Get password and cash from database
        user_info = db.execute(
            "SELECT cash, hash FROM users WHERE id = (?)", session.get("user_id"))[0]

        # Ensure password is correct
        if not check_password_hash(user_info["hash"], password):
            return apology("Invalid password", 403)

        # Perform operation
        new_cash = add_cash + user_info["cash"]

        # Update cash in database
        db.execute("UPDATE users SET cash = (?) WHERE id = (?)",
                   new_cash, session.get("user_id"))

        flash("Cash added successfully.")
        return redirect("/cash")

    return render_template("cash.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get user transactions
    user_history = db.execute(
        "SELECT * FROM stock_transactions WHERE user_id = (?) ORDER BY transaction_date DESC", session.get("user_id"))

    return render_template("history.html", user_history=user_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change password"""

    if request.method == "POST":

        # Check if user has writed the old password
        old_pass = request.form.get("old-password")
        if not old_pass:
            flash("Please provide your old password")
            return redirect("/password")

        # Check if user has writed the new password
        new_pass = request.form.get("new-password")
        if not new_pass:
            flash("Please provide your new password")
            return redirect("/password")

        # Check if old and new are different
        if old_pass == new_pass:
            flash("Your new password must be different than the old one.")
            return redirect("/password")

        # Ensure password has letter, symbol and number
        if not check_password(new_pass):
            flash("Password must contain letters, numbers and symbols")
            return redirect("/password")

        # Get current password from database
        user_password = db.execute(
            "SELECT hash FROM users WHERE id = (?)", session.get("user_id"))[0]["hash"]
        print(user_password)

        # Ensure password is correct
        if not check_password_hash(user_password, old_pass):
            return apology("Invalid password", 403)

        # Update password in database
        db.execute("UPDATE users SET hash = (?) WHERE id = (?)",
                   generate_password_hash(new_pass), session.get("user_id"))

        flash("Password changed successfully.")
        return redirect("/password")

    return render_template("password.html")


@app.route("/profile")
@login_required
def profile():
    """Display profile"""

    user_info = db.execute(
        "SELECT * FROM users WHERE id = (?)", session.get("user_id"))[0]

    return render_template("profile.html", username=user_info["username"], cash=user_info["cash"])


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Get and ensure that user inputed a symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please provide a stock's symbol.", 400)

        # Get stock's info from API
        response = lookup(symbol)
        if not response:
            return apology("No results where found for this stock's symbol.", 400)

        # Everything went well
        return render_template("quoted.html", symbol=symbol, response=response)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide Username.", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("Must provide Password.", 400)

        # Ensure password confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("Must provide Confirmation.", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Password and confirmation must be equal.", 400)

        # Ensure username is available
        if db.execute("SELECT * FROM users WHERE username = ?",
                      request.form.get("username")):
            return apology("Username is already in use.", 400)

        # Ensure password has letter, symbol and number
        if not check_password(request.form.get("password")):
            flash("Password must contain letters, numbers and symbols")
            return redirect("/register")

        # Insert into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        flash("Registration done successfully.")
        return redirect("/register")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Retrieve data related to user
    user_data = db.execute(
        "SELECT stock_name, SUM(total_shares) AS total_shares FROM stock_transactions WHERE user_id = ? GROUP BY stock_name;",
        session.get("user_id"))

    # Get parameters. Jinja will handle correct rendering
    symbol = request.args.get("symbol")

    if request.method == "POST":

        # Get and ensure that user inputed a symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please provide a stock symbol.", 400)

        # Get and ensure that user inputed a share
        shares = request.form.get("shares")
        if not shares:
            return apology("Please provide a quantity of shares.", 400)

        # Convert shares to int
        try:
            shares = int(shares)
        except ValueError:
            return apology("The quantity of shares must be an integer.", 400)

        # Check if shares is a positive number
        if shares <= 0:
            return apology("Number of shares must be greater than 0.", 400)

        # Check if user has a share with the inputed symbol and save index
        matching_index = None
        for i, data in enumerate(user_data):
            if data['stock_name'] == symbol:
                matching_index = i
                break

        # Flash message if the result was none, otherwise correct the quantity of shares, if necessary
        if matching_index == None:
            return apology("You don't own any shares of this stock.", 400)
        else:
            if user_data[matching_index]["total_shares"] < shares:
                return apology("Invalid number of shares.", 400)
                # shares = user_data[matching_index]["total_shares"]

        # Retrieve current value of share and perform calculations
        # The existence of the symbol was validated in the moment of the purchase
        response = lookup(symbol)
        unit_price = response["price"]
        total_price = unit_price * shares

        # Get user's cash and update value
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = (?)", session.get("user_id"))[0]["cash"]
        new_user_cash = total_price + user_cash
        db.execute("UPDATE users SET cash = (?) WHERE id = (?)",
                   new_user_cash, session.get("user_id"))

        transaction_type = "SELL"
        shares = -shares

        # Insert the sell data into the sell table
        db.execute("INSERT INTO stock_transactions (user_id, type, stock_name, total_shares, share_value, transaction_value, transaction_date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session.get("user_id"), transaction_type, symbol, shares, unit_price, total_price, datetime.now())

        return redirect("/")

    return render_template("sell.html", user_data=user_data, symbol=symbol)

if __name__ == "__main__":
    app.run(debug=True, port=3000)