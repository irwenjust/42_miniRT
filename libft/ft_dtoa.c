#include "libft.h"

char *ft_dtoa(double n)
{
    long int_part;
    int frac_part;
    char *res;
    int i = 0;

    // Split the number into integer and fractional parts
    int_part = (long)n;
    frac_part = (int)((n - int_part) * 10);
    if (frac_part < 0)
        frac_part = -frac_part;

    // Allocate memory: space for integer part, '.', fractional digit, and '\0'
    res = (char *)malloc(20); // 20 is enough for large integers with 1 fractional digit
    if (!res)
        return (NULL);

    // Handle the sign
    if (n < 0)
    {
        res[i++] = '-';
        int_part = -int_part;
    }

    // Convert the integer part to string
    char buffer[12];
    int int_len = 0;
    do
    {
        buffer[int_len++] = (int_part % 10) + '0';
        int_part /= 10;
    } while (int_part > 0);

    // Reverse and append to result
    while (int_len > 0)
        res[i++] = buffer[--int_len];

    // Add the decimal point and fractional part
    res[i++] = '.';
    res[i++] = frac_part + '0';

    // Null-terminate the string
    res[i] = '\0';

    return res;
}
