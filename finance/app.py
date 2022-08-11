import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    user_id = session["user_id"]
    # symbol, name, shares, price (current), total portfolio
    portfolio = db.execute("SELECT symbol,name,shares,price FROM buy WHERE user_id = ?", user_id)
    # update price (loop through portfolio)
    for asset in portfolio:
        quotedsymbol = lookup(asset["symbol"])
        current_price = quotedsymbol["price"]
        db.execute("UPDATE buy SET price = ? WHERE symbol == ?", current_price, quotedsymbol["symbol"])
    # current cash
    cur_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]
    # get current database
    up_port = db.execute("SELECT symbol,name,shares,price,total FROM buy WHERE user_id = ?", user_id)
    # grand total = cash + total portfolio
    sum_port = db.execute("SELECT SUM(total) FROM buy WHERE user_id = ?", user_id)[0]
    if sum_port["SUM(total)"] == None:
        sum_port["SUM(total)"] = 0
    grand_total = float(cur_cash["cash"]) + sum_port["SUM(total)"]

    # erase stocks with zero shares
    db.execute("DELETE FROM buy WHERE shares = '0'")

    return render_template("/index.html", up_port=up_port, cash=float(cur_cash["cash"]), grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        quotedsymbol = lookup(symbol)
        shares = request.form.get("shares")
        # user input is blank
        if symbol == None:
            return apology("Input is blank", 400)
        if shares == None:
            return apology("Input is blank", 400)
        # only set integers
        if shares.isdigit() == False:
            return apology("Invalid entry", 400)
        # check if input is > 0
        if int(float(shares)) <= 0:
            return apology("Invalid entry", 400)
        # check if input is numeric
        if shares.isnumeric() == False:
            return apology("Invalid entry", 400)
        if quotedsymbol == None:
            return apology("Invalid symbol", 400)

        date = request.form.get("date")
        transaction_amount = quotedsymbol["price"] * int(shares)
        balance = db.execute("SELECT cash FROM users WHERE id == ?", user_id)[0]

        if transaction_amount <= float(balance["cash"]):
            enough_cash = True
        else:
            return apology("Not enough funds", 403)

        if enough_cash:
            updated_cash = float(balance["cash"]) - transaction_amount
            db.execute("UPDATE users SET cash = ? WHERE id == ?", updated_cash, user_id)
            db.execute("INSERT INTO buy (user_id, symbol, name, shares, price, date) VALUES(?, ?, ?, ?, ?, ?)",
                       user_id, symbol, quotedsymbol["name"], shares, quotedsymbol["price"], date)
            db.execute("INSERT INTO transactions (user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, 'buy', symbol, shares, quotedsymbol["price"], date)
            return redirect("/")

    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    historic = db.execute("SELECT type,symbol,shares,price,date FROM transactions WHERE user_id = ?", user_id)

    return render_template("/history.html", historic=historic)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # ask user for input as post and look up for data
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quotedsymbol = lookup(symbol)
        if quotedsymbol == None:
            return apology("Invalid symbol", 400)
        else:
            return render_template("/quoted.html", name=quotedsymbol["name"], price=quotedsymbol["price"])

    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # register user via a form
    # return render_template("/register.html")
    if request.method == "POST":

        # render apology if username input is blank or already exists
        username = request.form.get("username")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not username:
            return apology("User input is blank", 400)
        if len(rows) == 1:
            return apology("Username already exists", 400)

        # render apology if password or confirmation is blank or password and confirmation do not match
        password = request.form.get("password")
        if not password:
            return apology("Password is blank", 400)

        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("Passwords do not match", 400)

        # register username & hash
        hash_pass = generate_password_hash(password, method='pbkdf2:sha256')
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pass)

        # remember user session (PENDING)
        # session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # sell share of stock that user owns
    user_id = session["user_id"]  # current user
    portfolio = db.execute("SELECT * FROM buy WHERE user_id = ?", user_id)  # all columns from buy table
    if request.method == "POST":
        symbol = request.form.get("symbol")  # get user input from form
        if symbol == None:
            return apology("Select a symbol", 400)
        else:
            shares = request.form.get("shares")
            num_shares = db.execute("SELECT shares FROM buy WHERE user_id = ? AND symbol = ?",
                                    user_id, symbol)[0]  # get num of shares with symbol
            if float(shares) > num_shares["shares"]:
                return apology("Too many shares", 400)
            if num_shares["shares"] == 0:
                return apology("You own 0 shares", 400)
            else:
                upd_shares = float(num_shares["shares"]) - float(shares)
                db.execute("UPDATE buy SET shares = ? WHERE user_id = ? AND symbol = ?", upd_shares, user_id, symbol)
            # update Cash
            # get current price
            quotedsymbol = lookup(symbol)
            current_price = quotedsymbol["price"]
            sold_cash = float(current_price) * float(shares)
            balance = db.execute("SELECT cash FROM users WHERE id == ?", user_id)[0]
            updated_cash = balance["cash"] + sold_cash
            db.execute("UPDATE users SET cash = ? WHERE id == ?", updated_cash, user_id)
            date = request.form.get("date")
            db.execute("INSERT INTO transactions (user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, 'sell', symbol, shares, current_price, date)

        return redirect("/")

    return render_template("/sell.html", portfolio=portfolio)

# change password call


@app.route("/change_password", methods=["GET", "POST"])
def page_change_password():

    user_id = session["user_id"]

    if request.method == "POST":
        new_password = request.form.get("password")
        if not new_password:
            return apology("Password is blank", 400)
        confirmation = request.form.get("confirmation")
        if new_password != confirmation:
            return apology("Passwords do not match", 400)

        new_hash_pass = generate_password_hash(new_password, method='pbkdf2:sha256')
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash_pass, user_id)

        return redirect("/")

    else:
        return render_template("/change_password.html")