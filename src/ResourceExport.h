#include <stdio.h>
#include <windows.h>

#ifdef _MSC_VER
int Export(const char *FilePath, int ResourceNumber, LPCSTR lpType)
{
    HRSRC HSRC = FindResourceA(NULL, MAKEINTRESOURCEA(ResourceNumber), lpType);
    DWORD ResourceSize = SizeofResource(NULL, HSRC);
    HANDLE ResourceHandle = LoadResource(NULL, HSRC);
    LPVOID ResourcePointer = LockResource(ResourceHandle);

    FILE *fp = fopen(FilePath, "wb");

    if (fp == NULL)
    {
        printf("fp is NULL!\n");
        return -1;
    }

    fwrite(ResourcePointer, ResourceSize, 1, fp);
    fclose(fp);

    return 0;
}
#elif __GNUC__
int Export(const char *FilePath, LPVOID BinaryBuffer)
{
    FILE *fp = fopen(FilePath, "wb");

    if (fp == NULL)
    {
        printf("fp is NULL!\n");
        return -1;
    }

    fwrite(BinaryBuffer, sizeof(*(BYTE *)BinaryBuffer), 1, fp);
    fclose(fp);

    return 0;
}
#endif
