from sys import exit, argv
from cs50 import SQL

if(len(argv) != 2):  # Checking Command Line Arguments Length
    print('Error')
    exit()      # Return 1
else:
    db = SQL("sqlite:///students.db")   # Connect dataBase
    for row in db.execute("SELECT first,middle,last,birth FROM STUDENTS WHERE house = ? ORDER BY last", argv[1]):
        if row['middle'] != None:
            print(row['first'] + ' ' + row['middle'] + ' ' + row['last'] + ', born ' + str(row['birth']))
        else:
            print(row['first'] + ' ' + row['last'] + ', born ' + str(row['birth']))
