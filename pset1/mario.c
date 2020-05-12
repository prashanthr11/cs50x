#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i = 0, j = 0, cnt = 0, z = 0, x = 0;
    // printf("Height: ");
    // scanf("%d", &x);
    do
    {
        x = get_int("Height: ");    // Gets Input
    }
    while (x > 8 || x < 1); // Checking Iput valuee
    j = x;
    cnt = x - 1;    // spaces
    for (i = 0; i < x; ++i) // loop for rows
    {
        for (j = 0; j < cnt; ++j) // loop for columns
        {
            printf(" ");    // Printing Spaces
        }
        for (z = cnt; z < x; ++z)   // loop for columns
        {
            printf("#");     // Printing Hash Symbols
        }
        printf("\n");   // New Line
        --cnt;  // Spaces Count in each column
    }               
}
