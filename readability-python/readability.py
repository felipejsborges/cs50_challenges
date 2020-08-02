# getting text from input
while True:
    text = (input("Text: "))
    if text:
        break

# counting letters, words and sentences
L, W, S = 0, 1, 0
for char in text:
    if char.isalpha():
        L += 1
    if char.isspace():
        W += 1
    if char == "." or char == "?" or char == "!":
        S += 1

# calculating Coleman-Liau index
gradeIndex = round(0.0588 * ((L / W) * 100) - 0.296 * ((S / W) * 100) - 15.8)

# printing result
if gradeIndex < 0:
    print("Before Grade 1")
elif gradeIndex >= 16:
    print("Grade 16+")
else:
    print(f"Grade {gradeIndex}")
