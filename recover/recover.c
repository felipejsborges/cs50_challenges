#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// defining BYTE as a unsigned int type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // verifying if the command line arguments usage is correct
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // opening .raw file
    FILE *fp = fopen(argv[1], "r");

    // getting file size in bytes
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // creating storage for file data
    BYTE buffer[size];

    //reading .raw file
    fread(buffer, 1, size, fp);

    // creating JPEG finded files counter
    int jpegCounter = 0;

    // creating an array to store JPEGs first byte position
    int jpegFirstBytePositions[100];

    // mapping all .raw file searching for benning of JPEGs
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
        {
            jpegFirstBytePositions[jpegCounter] = i;
            jpegCounter++;
        }
    }

    // creating the finded jpeg files
    for (int i = 0; i < jpegCounter; i++)
    {
        // creating a string to store the new jpeg file name
        char filename[10];
        sprintf(filename, "%03i.jpg", i);

        // openning this new file
        FILE *jfp = fopen(filename, "w");

        // handling last jpeg file
        int endOfNewJpgFileArray;
        if (i + 1 == jpegCounter)
        {
            endOfNewJpgFileArray = size;
        }
        else
        {
            endOfNewJpgFileArray = jpegFirstBytePositions[i + 1];
        }

        // creating an array to store each byte of the new file
        int newJpgFileArraySize = endOfNewJpgFileArray - jpegFirstBytePositions[i];
        BYTE newJpgFileArray[newJpgFileArraySize];

        // writting in the new jpeg file
        for (int j = jpegFirstBytePositions[i], counter = 0; j < endOfNewJpgFileArray; j++, counter++)
        {
            newJpgFileArray[counter] = buffer[j];
        }

        fwrite(newJpgFileArray, 1, newJpgFileArraySize, jfp);

        //closing JPEG file
        fclose(jfp);
    }

    // closing .raw file
    fclose(fp);
    return 0;
}
