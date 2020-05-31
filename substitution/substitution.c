#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char compare[27] = "";

    for (int i = 0; i < 26; i++)
    {
        if (!(isupper(key[i]) || islower(key[i])))
        {
            printf("There's one or more invalid characteres.\n");
            return 1;
        }

        for (int j = 0; j < strlen(compare); j++)
        {
            if (compare[j] == tolower(key[i]) || compare[j] == toupper(key[i]))
            {
                printf("There's one or more duplicated characteres.\n");
                return 1;
            }
        }

        compare[i] = key[i];

        compare[i + 1] = '\0';
    }

    string plaintext = get_string("plaintext: ");

    char ciphertext[99] = "";

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char cipherChar;
        if (isupper(plaintext[i]))
        {
            cipherChar = toupper(key[(int) plaintext[i] - 65]);
        }
        else if (islower(plaintext[i]))
        {
            cipherChar = tolower(key[(int) plaintext[i] - 97]);
        }
        else
        {
            cipherChar = plaintext[i];
        }
        int cipherLength = strlen(ciphertext);

        ciphertext[cipherLength] = cipherChar;

        ciphertext[cipherLength + 1] = '\0';
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}