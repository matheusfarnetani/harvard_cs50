#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define FILENAME_LENGTH 10

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Save file name
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 2;
    }

    // Skip Header of FAT
    fseek(inptr, BLOCK_SIZE, SEEK_SET);

    // Create necessary variables for looping/reading
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;
    char filename[FILENAME_LENGTH];
    FILE *outptr = NULL;

    // Start reading files
    while (fread(&buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file (doesn't work with first file)
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            //Creates new file
            sprintf(filename, "%03d.jpg", counter);

            outptr = fopen(filename, "wb");
            if (outptr == NULL)
            {
                fclose(inptr);
                printf("Could not create %s.\n", filename);
                return 3;
            }
            printf("File created successfully: %s\n", filename);

            fwrite(buffer, BLOCK_SIZE, 1, outptr);
            counter++;
        }
        else if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }

    // Close file if it was open
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);
    return 0;
}