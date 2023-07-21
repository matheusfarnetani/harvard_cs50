#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage ./reverse [INPUT].wav [OUTPUT].wav\n");
        return 1;
    }

    // Get length of input and output
    size_t inLength = strlen(argv[1]);
    size_t outLength = strlen(argv[2]);

    // Ensure input and output are .wav
    if (inLength >= 4 && outLength >= 4)
    {
        if (strcmp(argv[1] + inLength - 4, ".wav") != 0)
        {
            printf("Input must be .wav\n");
            return 1;
        }
        else if (strcmp(argv[2] + outLength - 4, ".wav") != 0)
        {
            printf("Output must be .wav\n");
            return 1;
        }
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file for reading
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (! check_format(header))
    {
        printf("Invalid .wav file\n");
        return 1;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        printf("Could not create %s\n", outfile);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Got to end of file
    fseek(inptr, blockSize, SEEK_END);

    // Write reversed audio to file    
    BYTE buffer[blockSize];
    while (ftell(inptr) - blockSize > sizeof(header))
    {
        // Go backwards
        fseek(inptr, -2 * blockSize, SEEK_CUR);

        // Read and write file
        fread(buffer, blockSize, 1, inptr);
        fwrite(buffer, blockSize, 1, outptr);
    }

    // Close files
    fclose(inptr);
    fclose(outptr);

    return 0;
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return true;
    }

    return false;
}

int get_block_size(WAVHEADER header)
{
    int bytesPerSample = header.bitsPerSample / 8;
    int blockSize = header.numChannels * bytesPerSample;

    return blockSize;
}