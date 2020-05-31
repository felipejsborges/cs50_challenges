#include <stdio.h>
#include <math.h>

// how does the Selection Sort Works? -> Θ(n²)
int main(void)
{
    // unsorted array and it size
    int array[11] = {7, 9, 17, 1, 3, 11, 5, 2, 8, 23, 10};
    int arraySize = sizeof(array) / sizeof(int);
    int unsortedElements = arraySize;

    int start = 0;
    int index;

    // when all elements are sorted, stop it
    while (unsortedElements > 0)
    {
        int lowestValue = array[start];

        // start verify from 0 position of the array
        for (int i = start; i < arraySize; i++)
        {
            // if the item is smallest, we need it to set on array[start]
            if (array[i] <= lowestValue)
            {
                index = i;
                lowestValue = array[i];
            }
        }
        // changing the position of first item with the lowest
        int cache = array[start];
        array[start] = lowestValue;
        array[index] = cache;

        // if we reach here, an element was sorted
        unsortedElements--;

        // starting in the next position of the array
        start++;
    }

    // showing the sorted array to the user
    printf("Sorted array: [");
    for(int j = 0; j < arraySize; j++)
    {
        if (j == arraySize - 1)
        {
            printf("%i", array[j]);
        }
        else
        {
            printf("%i, ", array[j]);
        }
    }
    printf("]\n");
}
