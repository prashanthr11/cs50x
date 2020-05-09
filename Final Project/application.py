from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import login_required

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response



# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")

@app.route("/")
@login_required
def Home_page():
    return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        user_name = request.form.get('username')
        login_password = request.form.get('password')
        first_name = request.form.get('first name')
        last_name = request.form.get('last name')
        email = request.form.get('mail')
        confirm_password = request.form.get('confirmation')
        address = request.form.get('address')
        city = request.form.get('city')
        ph_no = request.form.get('mobile number')
        pincode = request.form.get('pincode')


        if not user_name:
            return render_template("error.html", message = "must enter username", code=403)

        if not login_password:
            return render_template("error.html", message = "must enter password", code=403)

        if not first_name:
            return render_template("error.html", message = "must enter first name", code=403)

        if not last_name:
            return render_template("error.html", message = "must enter last name", code=403)

        if not login_password == confirm_password:
            return render_template("error.html", message = "Passwords Mismatch!", code=403)

        if not email:
            return render_template("error.html", message = "must enter Email ID", code=403)

        rows = db.execute("INSERT INTO users (username, first_name, last_name, email, password, address, city, mobile, pincode) VALUES(:username, :first_name, :last_name, :email, :password, :address, :city, :ph_no, :pincode)", {"username": user_name, "first_name": first_name, "last_name": last_name, "email":email, "password": login_password, "address": address, "city": city, "ph_no": ph_no, "pincode": pincode})

        # try:

        # except UNIQUE:
        #     return render_template("error.html", message="username taken", code=400)

        # Remember which user has logged in
        session["user_id"] = rows

        # Display a flash message
        flash("Registered!")

        # Redirect user to home page
        return redirect(url_for("login"))
    else:
        return render_template("register.html")




@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()
    if request.method == "POST":
        # return render_template("error.html", message = "welcome", code=403)

        user_name = request.form.get('username')
        login_password = request.form.get('password')

        if not user_name:
            return render_template("error.html", message = "must enter username", code=403)

        if not login_password:
            return render_template("error.html", message = "must enter password", code=403)

        check = db.execute("SELECT * FROM users WHERE  username = :username AND password = :password",{"username": user_name, "password": login_password})

        if not check:
            return render_template("error.html", message="Invalid User ID/ Password", code=403)

        # Remember which user has logged in
        session["user_id"] = check[0]["id"]

        # Display a flash message
        flash("Logged in Successfully!")

        return render_template("homepage.html")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect(url_for("login"))

@app.route("/homepage", methods=["GET", "POST"])
@login_required
def h_p():
    if request.method == "POST":

        name = request.form.get('name')
        search_cat = request.form.get("category")
        if search_cat == 'title':
            results = db.execute("SELECT * from shows WHERE title = :name", name = name)
        elif search_cat == 'type':
            results = db.execute("SELECT * from shows WHERE type = :name", name = name)
        elif search_cat == 'director':
            results = db.execute("SELECT * from shows WHERE director = :name", name = name)
        elif search_cat == 'country':
            results = db.execute("SELECT * from shows WHERE country = :name", name = name)

        return render_template("result.html", results = results)
    else:
        return render_template("homepage.html")



@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow user to change her password"""

    if request.method == "POST":


        # Ensure current password is not empty
        if not request.form.get("current_password"):
            return render_template("error.html", message="must provide password", code=403)

        # Ensure new password is not empty
        if not request.form.get("New_Password"):
            return render_template("error.html", message="must provide New Password", code=403)

        # Ensure confirm password is not empty
        if not request.form.get("Confirm Password"):
            return render_template("error.html", message="must provide Confirm Password", code=403)

        # Ensure new and confirm passwords match
        if not request.form.get("New_Password") == request.form.get("Confirm Password"):
            return render_template("error.html", message="Passwords not matched!", code=403)

        # Query database for user_id
        rows = db.execute("SELECT password FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Ensure current password is correct
        if len(rows) != 1:
            return render_template("error.html", message="Many users", code=403)

        # Update database
        # hash = generate_password_hash(request.form.get("new_password"))
        rows = db.execute("UPDATE users SET password = :newpassword WHERE id = :user_id", user_id=session["user_id"], newpassword=request.form.get("New_Password"))

        # Show flash
        flash("PAssword Changed!")

        return redirect("homepage")

    else:
        return render_template("changepassword.html")

@app.route("/contactus", methods=["GET", "POST"])
@login_required
def contact_us():

    if request.method == "POST":

         # Ensure name is not empty
        if not request.form.get("name"):
            return render_template("error.html", message="must provide name", code=403)

        # Ensure Mail ID is not empty
        if not request.form.get("email"):
            return render_template("error.html", message="must provide E-Mail ID", code=403)

        # Ensure Mobile Number is not empty
        if not request.form.get("ph_no"):
            return render_template("error.html", message="must provide Mobile Number", code=403)


        flash("Query Submitted!!")

        return redirect("homepage")
    else:
        return render_template("contactus.html")


@app.route("/myaccount")
@login_required
def my_account():
    details = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
    return render_template("myaccount.html", details = details)