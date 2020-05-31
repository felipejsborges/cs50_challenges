#include <stdio.h>
#include <math.h>

// how does the Bubble Sort Works? -> O(n²), Ω(n)
int main(void)
{
    // unsorted array and it size
    int array[10] = {7, 9, 17, 1, 3, 11, 5, 2, 17, 23};
    int arraySize = sizeof(array)/ sizeof(int);
    int swapArraySize = arraySize;

    // set swap counter to a non-zero value
    int swapCounter = -1;

    // repeat until the swap counter is 0, because when all elements are sorted, swapCounter is not going to be added
    while (swapCounter != 0)
    {
        // setting swap counter to zero to start the iteration
        swapCounter = 0;

        // looking at each adjacent pair
        for (int i = 0; i < swapArraySize - 1; i++)
        {
            // if they are not in order, swap them and add one to swap counter
            if (array[i] > array[i+1])
            {
                int cache = array[i];
                array[i] = array[i+1];
                array[i+1] = cache;
                swapCounter++;
            }
        }
        // when we just finish a iteration, the last item is sorted, so our array size is previous iteration size -1
        swapArraySize--;
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
