from sys import argv, exit
import csv
import sqlite3

# testing usage of command line arguments
if len(argv) != 2:
    print("Usage: python import.py csvFile.csv")
    exit(1)

# defining function to insert data into students table of students.db
def insertIntoTable(first, middle, last, house, birth):
    # connecting to database and instancing cursor
    sqliteConnection = sqlite3.connect('students.db')
    cursor = sqliteConnection.cursor()

    # executing query and sending changes
    values = (first, middle, last, house, int(birth))
    cursor.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);", values)
    sqliteConnection.commit()

    # closing cursor and connection to DB
    cursor.close()
    sqliteConnection.close()

# openning csv file for reading
with open (argv[1], 'r') as csvfile:
    csvreader = csv.DictReader(csvfile)

    # runing each row
    for row in csvreader:
        # getting and parsing names
        nameList = row['name'].split()

        first = nameList[0]

        last = nameList[len(nameList) - 1]

        middle = row['name'].replace(first, "")
        middle = middle.replace(last, "")
        middle = middle.replace(" ", "")
        if middle == "":
            middle = None

        # getting house and birth year
        house, birth = row['house'], row['birth']

        # calling function to insert it in students table on students DB
        insertIntoTable(first, middle, last, house, birth)
