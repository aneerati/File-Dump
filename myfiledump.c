#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filedump(char *p, int len)
{

    int counter = 0;
    unsigned long address = 0;
    unsigned char *q;
    q = (unsigned char *)p;

    for (int i = 0; i < len; i++)
    {
        int c = q[i];

        if (i % 16 == 0)
        {
            printf("0x%016lX: ", (unsigned long)i);
        }

        printf("%02X ", c);
        counter++;

        if (counter % 16 == 0)
        {
            printf(" ");
            for (int j = 0; j < 16; j++)
            {
                int d = q[i - 15 + j];
                printf("%c", (d >= 32 && d < 127) ? d : '.');
            }
            printf("\n");
            address += 16;
        }
    }

    if (counter % 16 != 0)
    {
        int spaces = (16 - (counter % 16)) * 3 + 1;
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < (counter % 16); i++)
        {
            int d = q[len - (counter % 16) + i];
            printf("%c", (d >= 32 && d < 127) ? d : '.');
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Error opening file \"%s\"\n", argv[1]);
        return 0;
    }

    fseek(file, 0L, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(filesize);
    if (buffer == NULL)
    {
        printf("Error creating buffer");
        fclose(file);
        return 0;
    }

    int read_contents = fread(buffer, 1, filesize, file);
    if (read_contents != filesize)
    {
        printf("Error reading contents");
        free(buffer);
        fclose(file);
        return 0;
    }

    if ((argv[2] != NULL) && (atoi(argv[2]) <= filesize))
    {
        filedump(buffer, atoi(argv[2]));
    }
    else
    {
        filedump(buffer, filesize);
    }

    free(buffer);
    fclose(file);
}