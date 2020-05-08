from cs50 import get_float
from sys import exit
import math


def main():
    while True:
        x = get_float("Change owed: ")  # Getting Input
        if x >= 0:      # checking Input x should be bon-negative number
            q = round(x * 100)  # Dollar to Cents
            get_change(q)
            exit(0)


cnt = count = 0


def check(a):
    global cnt
    if a >= 10:
        cnt += math.floor(a / 10)   # Counting Dimes
        b = a % 10
        check(b)
    elif a >= 5:
        cnt += math.floor(a / 5)  # Counting Nickels
        b = a % 5
        check(b)
    else:
        cnt += a    # Counting Pennies
        print(round(count + cnt))   
        return


def get_change(m):
    global count
    count = math.floor(m / 25)  # Counting No of Quarters or 25 cents coins
    a = m % 25      # Remaining change ranges from(0 to 24)
    check(a)    # Counting Minimum No of Coins Required
 

main()
