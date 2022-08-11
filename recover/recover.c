#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check if memory card file is typed
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open file to read
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }

    // allocate memory to block
    BYTE *block = malloc(sizeof(BYTE) * 512);
    if (block == NULL)
    {
        printf("Error");
        return 3;
    }

    int count = 0;
    char filename[8];

    FILE *output = NULL;


    // loop to check if size of data is 512 bytes
    while (fread(block, sizeof(BYTE), 512,  input) == 512)
    {
        // check if firsts hexa of array are jpeg bytes
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && ((block[3] & 0xf0) == 0xe0))
        {
            // if first jpeg, write first jpeg
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not create %s\n", filename);
                    return 5;
                }
                fwrite(block, sizeof(BYTE), 512, output); // si retorna 512 bytes, escribe; sino se detiene
                count++;
            }
            else if (count > 0)
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", count);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not create %s\n", filename);
                    return 5;
                }
                // creating a buffer to store the jpeg name
                fwrite(block, sizeof(BYTE), 512, output);
                count++;
            }
        }
        else
        {
            if (count == 0)
            {
                continue;
            }
            else if (count > 0)
            {
                fwrite(block, sizeof(BYTE), 512,  output);
            }
        }
    }

    //close remaining files
    free(block);
    fclose(output);
    fclose(input);
    return 0;
}