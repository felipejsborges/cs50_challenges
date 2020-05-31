#include <stdio.h>
#include <math.h>

// how does the Linear Search Works? -> O(n), Ω(1)
int main(void)
{
    // what is our target?
    int x = 9;

    // in what array?
    int array[7] = {1, 3, 5, 7, 9, 11, 17};
    int arraySize = sizeof(array)/ sizeof(int);

    // look each item of the array, starting at the first element
	for (int i = 0; i < arraySize; i++)
	{
	    // if this item is the target, stop
		if (array[i] == x)
		{
			printf("Found x: %i em %i iteractions\n", array[i], i);
			return 0;
		}
		// otherwise, move to the next element
	}
	// if we reach here, our target does not exist in the array
	printf("Not found\n");
	return 1;
}
