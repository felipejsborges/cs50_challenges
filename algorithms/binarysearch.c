#include <stdio.h>
#include <math.h>

// how does the Binary Search Works? - O(log n), Ω(1) - it just works if the array is sorted
int main(void)
{
    // what is our target?
    int x = 4;

    // in what array?
    int array[9] = {1, 3, 4, 7, 9, 11, 17, 23, 25};
    int arraySize = sizeof(array) / sizeof(int);

    // defining checkpoints
    int startPoint = 0;
    int endPoint = arraySize - 1;

    // calculate the middle pointo of the current (sub)array
    int half = (startPoint + endPoint) / 2;

    // if the target is out of the range, it could not be found
    if (x < array[startPoint] || x > array[endPoint])
    {
        printf("Out of range\n");
        return 1;
    }

    while((endPoint - startPoint) >= 0) // repeat until the (sub)array is of size 0
    {
        // if the target is the middle, stop
        if (array[half] == x)
    	{
    		printf("Found x: %i\n", array[half]);
    		return 0;
    	}

        // if the target is greater than middle, change the start point to be the right of middle
    	if (x > array[half])
    	{
    		startPoint = half + 1;
    	}
    	// if the target is less than middle, change the end point to be the left of middle
    	else
    	{
    		endPoint = half - 1;
    	}

    	// calculate the middle point of the current (sub)array
        half = (startPoint + endPoint) / 2;
    }
    printf("Not found\n");
    return 1;
}
