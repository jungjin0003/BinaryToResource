#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    char header[] = "BEGIN\n\t";
    
    if (argc != 3)
    {
        printf("Usage: %s [Binary File] [Output File]\n", argv[0]);
        exit(0);
    }

    FILE *fp = fopen(argv[1], "rb");

    if (fp == NULL)
    {
        printf("fp is NULL!\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned short *Data = malloc(size);
    fread(Data, size, 1, fp);
    fclose(fp);

    fp = fopen(argv[2], "wb");

    if (fp == NULL)
    {
        printf("fp is NULL\n");
        exit(0);
    }

    fprintf(fp, "%s", header);

    int i = 0;
    int count = 0;

    for (; i < (size - 2) / 2; i++)
    {
        if (count == 8)
        {
            fprintf(fp, "0x%04x, \n    ", *(Data + i));
            count = 0;
            continue;
        }
        fprintf(fp, "0x%04x, ", *(Data + i));
        count++;
    }

    fprintf(fp, "0x%04x \nEND", *(Data + i));

    fclose(fp);

    free(Data);
}