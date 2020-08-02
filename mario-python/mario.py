while True:
    try:
        n = int((input("Height: ")))
        if n > 0 and n <= 8:
            break
    except ValueError:
        pass

for i in range(1, n + 1, 1):
    print(" " * (n - i), "#" * i, "  ", "#" * i)