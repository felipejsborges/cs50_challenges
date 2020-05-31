#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    long cardNumber;
    
    do
    {
        cardNumber = get_long("Number: ");
    }
    while(cardNumber<1);
    
    int cardNumberLength = floor(log10(labs(cardNumber))) + 1;
    
    int sum = 0;
        
    for (int i = 1; i <= cardNumberLength; i++)
    {
        long raised = pow(10, i);
        
        int digit = ((cardNumber % raised) / (raised / 10));
       
        if (i % 2 == 0)
        {
            int doubledDigit = digit * 2;
            int doubledDigitLength = floor(log10(labs(doubledDigit))) + 1;
            
            if (doubledDigitLength == 1)
            {
                sum += doubledDigit;
            } 
            else 
            {
                for (int j = 1; j <= doubledDigitLength; j++)
                {
                    long raisedToDoubleDigits = pow(10, j);
        
                    int individualDoubledDigit = ((doubledDigit % raisedToDoubleDigits) / (raisedToDoubleDigits / 10));
                    
                    sum += individualDoubledDigit;
                }
            }
        } 
        else 
        {
            sum += digit;
        }
    }
    
    if (sum % 10 == 0)
    {
        long raisedToFirstDigits = pow(10, cardNumberLength);
        
        int firstDigit = ((cardNumber % raisedToFirstDigits) / (raisedToFirstDigits / 10));
        
        int secondDigit = ((cardNumber % (raisedToFirstDigits/10)) / (raisedToFirstDigits / 100));
        
         if (cardNumberLength == 15 && firstDigit == 3 && (secondDigit == 4 || secondDigit == 7)) {
            printf("AMEX\n");
         }
         else if (cardNumberLength == 16 && firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)) {
            printf("MASTERCARD\n");
         } 
         else if ((cardNumberLength == 13 || cardNumberLength == 16) && firstDigit == 4)
         {
            printf("VISA\n");
         } 
         else
         {
            printf("INVALID\n");
         }
    } 
    else 
    {
        printf("INVALID\n");
    }
}