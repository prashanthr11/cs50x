from sys import exit, argv
from cs50 import SQL
import csv

if (len(argv) != 2):    # Checking Command Line Arguments Length
    print('Error')
    exit()      # Return 1
else:
    db = SQL("sqlite:///students.db")   # Connect dataBase
    with open(argv[1], 'r') as file:    # Opening file in argv[1]
        data = csv.reader(file)

        id = 0

        for i in data:      # Iterate through the each lines of the file
            id += 1
            l = i[0].split()    # Split tthe words into First, Middle, Last Names amd Inset into the DB
            if len(l) == 2:     # Middle Name is NULL
                db.execute("INSERT INTO students VALUES (?, ?, ? , ?, ?, ?)", id, l[0], None, l[1], i[1], i[2])
            elif len(l) == 3:
                db.execute(f"INSERT INTO students VALUES (?, ?, ? , ?, ?, ?)", id, l[0], l[1], l[2], i[1], i[2])
            else:
                id -= 1     # Column Names
