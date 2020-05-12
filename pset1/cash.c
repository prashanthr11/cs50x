# include<cs50.h>
# include <stdio.h>
# include <math.h>

int b = 0, cnt = 0, c = 0, d = 0, count = 0;
float x;

int check(int a)
{
    if (a >= 10)
    {
        cnt += a / 10;  // Counting Dimes
        b = a % 10;   
        check(b);
    }
    else if (a >= 5) 
    {
        cnt += a / 5;   // Counting Nickels
        b = a % 5;
        check(b);
    }
    else if (a < 5) 
    {
        cnt +=  a;   // Counting Pennies
    }
    return cnt;
}

int get_change(int m)   // Counting No of Quarters or 25 cents coins
{
    d = m / 25;
    int a = m % 25;     // Remaining change ranges from(0 to 24)
    count = d + check(a);   // Counting Minimum No of Coins Required
    return count;
}
int main(void) 
{
    do
    {    
        x = get_float("Change owed: "); // Getting Input
    }
    while (x <= 0);     // checking Input x should be bon-negative number
    int q = round(x * 100);     // Dollar to Cents
    printf("%i\n", get_change(q));
}

