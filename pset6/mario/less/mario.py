from cs50 import get_int
from sys import exit

while True: 
    x = get_int('Height: ')     # Get Input
    if x > 0 and x < 9:     # Condition
        cnt = x - 1     # Spaces
        for i in range(x):
            for j in range(cnt):
                print(' ', end='')      # Print Spaces
                # print('\n')
            for z in range(cnt, x):
                print("#", end='')       # Print Symbols--> '#'
            print('')       # New Line
            cnt -= 1
        exit(0)     # return 0

