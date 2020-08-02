from sys import argv, exit
import csv

# testing usage of command line arguments
if len(argv) != 3:
    print("Usage: python dna.py csvFile.csv textFile.txt")
    exit(1)

# creating function to test repetition of a same STR in a DNA
def countSTRs(str, dna, dnaIndex, sequenceCounter):
    dnaIndex = dnaIndex + len(str)
    tmp = dnaIndex + len(str)
    if str == (dna[dnaIndex:tmp]):
        sequenceCounter += 1
        return countSTRs(str, dna, dnaIndex, sequenceCounter)
    else:
        return sequenceCounter

# creating list to store strCounters
strCounterList = []
# openning database file
with open(argv[1], "r") as databaseFile:
    # reading csv file
    csv_reader = csv.reader(databaseFile, delimiter=',')
    line_counter = 0
    # reading each row in the csv
    for row in csv_reader:
        line_counter += 1
        if line_counter == 1:
            # reading each column of a row in csv
            for i in range(1, len(row), 1):
                # getting STR
                str = row[i]
                strCounter = 0
                # reading DNA
                with open(argv[2], "r") as dnaFile:
                    for dna in dnaFile:
                        # reading each char of the DNA
                        for dnaIndex in range(0, len(dna) - len(str), 1):
                            # testing if it's equal of the STR
                            if str == (dna[dnaIndex:(dnaIndex + len(str))]):
                                # counting sequences
                                countSequences = countSTRs(str, dna, dnaIndex, 1)
                                if (strCounter < countSequences):
                                    strCounter = countSequences
                    # adding sequences counter to list
                    strCounterList.append(strCounter)
        else:
            # creating a list of sequences in a row of database to compare with the dna sequences
            compareList = []
            for i in range(1, len(row), 1):
                compareList.append(int(row[i]))
            # if it matches, print the person name
            if compareList == strCounterList:
                print(row[0])
                exit(0)

# print result if it does not match to anybody
print("No match")
