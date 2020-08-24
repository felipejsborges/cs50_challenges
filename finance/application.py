import os
# from cs50 import SQL
import sqlite3
from flask import Flask, flash, jsonify, redirect, render_template, request, session, json
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# dict factory to parse data got in DB
def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

# function to get data from DB
def db(action, query, values):
    # connect to DB and create cursor
    connection = sqlite3.connect('finance.db')
    connection.row_factory = dict_factory
    cursor = connection.cursor()

    # executing query
    try:
        cursor.execute(query, values)
        if action == "read":
            result = cursor.fetchall()
        elif action == "create":
            connection.commit()

        # closing cursor and connection to DB
        cursor.close()
        connection.close()

        return result
    except:
        return apology("Error on execute queries on database")

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
# db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # get user cash
    action = "read"
    values = (session["user_id"],)
    query = "SELECT cash FROM users WHERE id = ?;"
    userResult = db(action, query, values)
    cash = userResult[0]['cash']
    total = cash

    # Get stocks by this user
    action = "read"
    query = "SELECT stock_symbol, stock_name FROM transactions WHERE user_id = ? GROUP BY stock_symbol ORDER BY quantity DESC;"
    values = (session["user_id"],)
    stocks = db(action, query, values)

    # get data for each stock
    data = []
    for stock in stocks:
        # get bought data
        action = "read"
        values = (session["user_id"], stock["stock_symbol"])
        query = "SELECT AVG(stock_price) AS average_price_on_buy, quantity, total FROM transactions WHERE operation = 'buy' AND user_id = ? AND stock_symbol = ? GROUP BY stock_symbol;"
        bougthResult = db(action, query, values)

        # get sold data
        query = "SELECT quantity, total FROM transactions WHERE operation = 'sell' AND user_id = ? AND stock_symbol = ? GROUP BY stock_symbol;"
        soldResult = db(action, query, values)

        # parsing result
        if not soldResult:
            soldResult = [{}]
            soldResult[0]['quantity'], soldResult[0]['total'] = 0, 0

        boughtData = bougthResult[0]
        soldData = soldResult[0]

        actualQuantityOnAccount = boughtData['quantity'] - soldData['quantity']

        # it will be displayed only if it has this stock on account
        if actualQuantityOnAccount > 1:
            # get current data from api
            stockInfo = lookup(stock['stock_symbol'])
            priceNow = stockInfo["price"]

            # calc profit
            totalBoughtOnAccount = boughtData['average_price_on_buy'] * actualQuantityOnAccount
            totalNow= actualQuantityOnAccount * priceNow
            profit = totalNow - totalBoughtOnAccount
            profiftPercentage = (profit / totalBoughtOnAccount)

            if profit > 0 :
                profitResult = 'positive'
            elif profit < 0 :
                profitResult = 'negative'
            else:
                profitResult = 'zero'

            total += totalNow

            # handle data to be displayed
            stockData = {
                'symbol': stock['stock_symbol'],
                'name': stock['stock_name'],
                'shares':  actualQuantityOnAccount,
                'averagePriceOnBuy': usd(boughtData['average_price_on_buy']),
                'totalBought': usd(totalBoughtOnAccount),
                'priceNow': usd(priceNow),
                'profit': usd(profit),
                'profitPercentage': f"{profiftPercentage:.2%}",
                'totalNow': usd(totalNow),
                'profitResult': profitResult,
            }
            data.append(stockData)

    return render_template("index.html", data=data, total=usd(total), cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # get symbol from form
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide a symbol.")

        # get stock information
        stockInfo = lookup(symbol)
        if not stockInfo:
            return apology("This stock does not exist")
        stockSymbol = stockInfo["symbol"]
        stockName = stockInfo["name"]
        stockPrice = stockInfo["price"]

        # get shares from form
        shares = request.form.get("shares")
        if not shares:
            return apology("You must provide a share quantity.")


        # get user balance
        action = "read"
        query = "SELECT cash FROM users WHERE id = ?;"
        values = (session["user_id"],)
        userBalance = db(action, query, values)


        # check user balance
        totalCost = stockPrice * int(shares)
        if userBalance[0]['cash'] < totalCost:
            return apology("Not enough cash in your balance.")

        # save transaction on DB
        action = "create"
        query = "INSERT INTO transactions (operation, stock_symbol, stock_name, stock_price, quantity, total, user_id) VALUES (?, ?, ?, ?, ?, ?, ?);"
        values = ('buy', stockSymbol, stockName, stockPrice, shares, totalCost, session["user_id"])
        db(action, query, values)

        # update user balance
        action = "create"
        query = "UPDATE users SET cash = ? WHERE id = ?;"
        newBalance = userBalance[0]['cash'] - totalCost
        values = (newBalance, session["user_id"])
        db(action, query, values)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    # Get transactions by this user
    action = "read"
    query = "SELECT * FROM transactions WHERE user_id = ?;"
    values = (session["user_id"],)
    transactions = db(action, query, values)

    return render_template("history.html", data=transactions)


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
        action = "read"
        query = "SELECT * FROM users WHERE username = ?"
        values = (request.form.get("username"),)
        rows = db(action, query, values)

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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide a symbol.")

        result = lookup(symbol)
        if not result:
            return apology("This stock does not exist")
        else:
            result["price"] = usd(result["price"])
            return render_template("quote.html", result=result)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        if not username:
            return apology("You must provide a username.")
        password = request.form.get("password")
        if not password:
            return apology("You must provide a password.")
        passwordConfirmation = request.form.get("passwordConfirmation")
        if not (passwordConfirmation == password):
            return apology("Password does not match")

        action = "create"
        query = "INSERT INTO users (username, hash) VALUES (?, ?);"
        values = (username, generate_password_hash(password))
        db(action, query, values)

        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        # Get stocks by this user
        action = "read"
        query = "SELECT stock_symbol, stock_name FROM transactions WHERE user_id = ? GROUP BY stock_symbol ORDER BY quantity DESC;"
        values = (session["user_id"],)
        stocks = db(action, query, values)

        # Get quantity of each stock and put data in an array
        counter = 0
        data = []
        for stock in stocks:
            # get bought quantity
            action = "read"
            values = (session["user_id"], stock["stock_symbol"])
            query = "SELECT quantity FROM transactions WHERE operation = 'buy' AND user_id = ? AND stock_symbol = ? GROUP BY stock_symbol;"
            bougthResult = db(action, query, values)
            boughtQuantity= bougthResult[0]['quantity']

            # get sold quantity
            query = "SELECT quantity FROM transactions WHERE operation = 'sell' AND user_id = ? AND stock_symbol = ? GROUP BY stock_symbol;"
            soldResult = db(action, query, values)

            # parsing result
            if not soldResult:
                soldResult = [{}]
                soldResult[0]['quantity'], soldResult[0]['total'] = 0, 0
            soldQuantity = soldResult[0]['quantity']

            actualQuantityOnAccount = boughtQuantity - soldQuantity

            # it will be displayed only if it has this stock on account
            if actualQuantityOnAccount > 1:
                counter += 1
                # handle data to be displayed
                stockData = {
                    'symbol': stock['stock_symbol'],
                    'quantity':  actualQuantityOnAccount,
                    'index': counter
                }
                data.append(stockData)

        return render_template("sell.html", data=data)

    else:
        # get data from html page
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # get stock current price
        stockInfo = lookup(symbol)
        stockName = stockInfo["name"]
        stockPrice = stockInfo["price"]

        totalSold = stockPrice * int(shares)

        # save transaction on DB
        action = "create"
        query = "INSERT INTO transactions (operation, stock_symbol, stock_name, stock_price, quantity, total, user_id) VALUES (?, ?, ?, ?, ?, ?, ?);"
        values = ('sell', symbol, stockName, stockPrice, shares, totalSold, session["user_id"])
        db(action, query, values)

        # get user balance
        action = "read"
        query = "SELECT cash FROM users WHERE id = ?;"
        values = (session["user_id"],)
        userBalanceResult = db(action, query, values)

        # add sold cash to user balance and update it on DB
        action = "create"
        query = "UPDATE users SET cash = ? WHERE id = ?;"
        finalUserBalance = userBalanceResult[0]['cash'] + totalSold
        values = (finalUserBalance, session["user_id"])
        db(action, query, values)

        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
