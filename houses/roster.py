from sys import argv, exit
import sqlite3

# testing usage of command line arguments
if len(argv) != 2:
    print("Usage: python roster.py HouseName")
    exit(1)

# connecting to database and instancing cursor
sqliteConnection = sqlite3.connect('students.db')
cursor = sqliteConnection.cursor()

# executing query and getting result
cursor.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first;", (argv[1],))
result = cursor.fetchall()

# running result data
for row in result:
    # getting name and birth year
    first, middle, last, birth = row[0], row[1], row[2], row[3]

    # checking for NULL middle values and print out each student full name and birth year
    if middle == None:
        print (f"{first} {last}, born {birth}")
    else:
        print (f"{first} {middle} {last}, born {birth}")

# closing cursor and connection to DB
cursor.close()
sqliteConnection.close()
