#include <stdio.h>
#include <math.h>

// how does the Selection Sort Works? -> Θ(n²)
int main(void)
{
    // unsorted array and it size
    int array[8] = {7, 3, 17, 1, 9, 3, 11, 5};
    int arraySize = sizeof(array) / sizeof(int);

    // call the first element of the array "sorted"
    int sortedElements = 1;

    // repeat util all elements are sorted
    while (sortedElements < arraySize)
    {
        // Look at the next unsorted element and call it "sorted" by shifting the requisite number of elements
        int cache = array[sortedElements];
        int sliceCount = 0;

        // look back and see if it is sorted
        for (int i = sortedElements - 1; i >= 0 ; i--)
        {
            // checking if need to slice the element
            if (cache < array[i])
            {
                array[sortedElements-sliceCount] = array[sortedElements-sliceCount-1];
                sliceCount++;
            }
        }
        array[sortedElements-sliceCount] = cache;
        sortedElements++;
    }

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
