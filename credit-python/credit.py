import math
from sys import exit

while True:
    # getting number from input
    cardNumber = (input("Number: "))

    # testing if it's a positive number
    try:
        cardNumberInt = int(cardNumber)
        if cardNumberInt > 0:
            break
    except ValueError:
        pass

cardLength = len(cardNumber)
sum = 0

# applying Luhn’s algorithm
for x in range(cardLength, 0, -1):
    number = cardNumber[x - 1]
    if ((cardLength - x) % 2 == 0):
        sum += int(number)
    else:
        evenSum = int(number) * 2
        if len(str(evenSum > 1)):
            sum += (evenSum) % 10
            sum += math.floor((evenSum) / 10)
        else:
            sum += evenSum

if (sum % 10 != 0):
    print("INVALID\n")
    exit (1)

# getting credit card operator
firstDigit = cardNumber[0:1]
secondDigit = cardNumber[1:2]

if (cardLength == 15 and firstDigit == "3" and (secondDigit == "4" or secondDigit == "7")):
    print("AMEX\n")
elif (cardLength == 16 and firstDigit == "5" and (secondDigit == "1" or secondDigit == "2" or secondDigit == "3" or secondDigit == "4" or secondDigit == "5")):
    print("MASTERCARD\n")
elif ((cardLength == 13 or cardLength == 16) and firstDigit == "4"):
    print("VISA\n")
else:
    print("INVALID\n")
