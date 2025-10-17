#include <stdio.h>

char *strcpy(char *dst, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i]='\0';
    return dst;
}


int main(int argc, char const *argv[])
{
    char str1[]= "loki";
    char str2[7];
    strcpy(str2, str1);
    printf("%s",str2);
    return 0;
}


