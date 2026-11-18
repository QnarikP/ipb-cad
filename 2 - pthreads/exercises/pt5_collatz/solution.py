p = int(input('Enter a number: '))
while True:
    if p % 2 == 0:
        p = int(p / 2)
    else:
        p = 3 * p + 1
    print(p)
    if p == 1:
        break
