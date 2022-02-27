height = 0

# prompting user until right input
while (height < 1 or height > 8):
    try:
        height = int(input("Height: "))
    except ValueError:
        continue

# traversing through each level
for i in range(height):
    # number of leading spaces for each level
    spaces = height - i - 1

    # number of hashes for each level
    hashes = i + 1

    print(" " * spaces, end="")
    print("#" * hashes, end="  ")
    print("#" * hashes)