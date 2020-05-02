# include <stdio.h>
# include <cs50.h>
# include <math.h>
# include <string.h>

int main()
{
    
    float letters = 1, words = 1, sentences = 0;
    string x = get_string("Text : ");   // Getting Input
    // printf("%s\n", x);
    
    for (int i = 1; i < strlen(x); ++i) 
    {
        if ((x[i] >= 'A' && x[i] <= 'Z') || (x[i] >= 'a' && x[i] <= 'z') || x[i] == '-')
        {
            letters++;  // Letters Count
            printf("%c",x[i]);
        }
        if (x[i] == ' ') 
        {
            ++words;    // Words Count
            if (x[i + 1] == ' ')
            {
                --words;    // Adjacent Spaces
            }
        }
        
        if (x[i] == '.' || x[i] == '!' || x[i] == '?')
        {
            ++sentences;    // Sentences Count
        }
    }
    
    float L = letters / words * 100;
    float S = sentences / words * 100;

    printf("%f\n%f\n%f\n%f\n%f\n", letters, words,sentences,L, S);
    int index = round(0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8);
    
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16) 
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}
