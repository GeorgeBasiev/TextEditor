#include <stdbool.h>
#include <stdlib.h>

bool IsPositiveNumeric(char* str) 
{
    if (str == NULL || *str == '\0' || *str == '-' || *str == '+')
        return false;

    bool has_digits = false;
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            has_digits = true;
            ++str;
        } 
        else 
            return false; 
    }


    return has_digits; 
}

int StrCmp(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return (int)str1[i] - (int)str2[i];
}

int Length(char* str)
{
    int len = 0;
    while (*str != '\0') {
        ++len;
        ++str;
    }
    return len;
}