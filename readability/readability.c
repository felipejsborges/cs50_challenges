#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int lettersCountFunction(string text, int stringLength);
int wordsCountFunction(string text, int stringLength);
int sentencesCountFunction(string text, int stringLength);

int main(void)
{
    string text = get_string("Text: ");

    int stringLength = strlen(text);

    int lettersCount, wordsCount, sentencesCount;

    lettersCount = lettersCountFunction(text, stringLength);

    wordsCount = wordsCountFunction(text, stringLength);

    sentencesCount = sentencesCountFunction(text, stringLength);

    double l = (((double) lettersCount) / ((double) wordsCount)) * 100;

    double s = (((double) sentencesCount) / ((double) wordsCount)) * 100;

    double index = round(0.0588 * l - 0.296 * s - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

int lettersCountFunction(string text, int stringLength)
{
    int count = 0;

    for (int i = 0; i < stringLength; i++)
    {
        int letterInt = (int) text[i];

        if (islower(letterInt) || isupper(letterInt))
        {
            count++;
        }
    }
    return count;
}

int wordsCountFunction(string text, int stringLength)
{
    int count = 1;

    for (int i = 2; i < stringLength; i++)
    {
        int c = isspace(text[i]);

        int prevc = isspace(text[i - 1]);

        if (c != 0 && prevc == 0)
        {
            count++;
        }
    }
    return count;
}

int sentencesCountFunction(string text, int stringLength)
{
    int count = 0;

    for (int i = 0; i < stringLength; i++)
    {
        char c =  text[i];

        if (c == '.' || c == '!'  || c == '?')
        {
            count++;
        }
    }
    return count;
}
