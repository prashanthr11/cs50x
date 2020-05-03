# include <stdio.h>
# include <stdlib.h>
# include <cs50.h>
# include <ctype.h>
# include <string.h>
int main(int argc, string argv[])
{
    if (argc != 2)  // Checking Argumnet-Count
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); ++i)   // loop through the 1st argument for checking non-integer values
    {
        if ((argv[1][i] >= 'A' && argv[1][i] <= 'z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z'))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string input = get_string("plaintext: "); // Input String
    char lower[27], upper[27];  // creating strings for both Upper & Lower letters
    char q = 'a';
    for (int j = 0; j <= 25; ++q, ++j)
    {
        lower[j] = q;   
    }
    char x = 'A';
    for (int j = 0; j <= 25; ++x, ++j)
    {
        upper[j] = x;
    }
    int k = atoi(argv[1]);  // coverting string to int
    for (int i = 0; i < strlen(input); ++i)
    {
        if (isalpha(input[i]) && isupper(input[i])) // Both Alphabet and Uppercase Letter
        {
            input[i] = upper[((input[i] + k) % 65) % 26]; // 'Z' + 3 (Say) = 93 % 65 = 28 % 26 = 2 --> upper[2] = 'C'
        }
        else if (isalpha(input[i]) && islower(input[i]))    // Both Alphabet and Lowercase Letter
        {
            input[i] = lower[((input[i] + k) % 97) % 26]; // 'z' + 3 (Say) = 125 % 97 = 28 % 26 = 2 --> lower[2] = 'c'
        }
    }
    printf("ciphertext: %s\n", input);
    return 0;
}
