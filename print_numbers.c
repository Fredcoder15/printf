#include "main.h"

/**
 * print_unsigned_digits - Prints an unsigned number recursively.
 * @n: Number to print.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
static int print_unsigned_digits(unsigned long int n, char *buffer,unsigned int *index)
{
    int count = 0;
    int result;

    if (n >= 10)
    {
        result = print_unsigned_digits(n / 10, buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_char((n % 10) + '0', buffer, index);
    if (result == -1)
    {
        return (-1);
    }

    return (count + result);
}

/**
 * print_unsigned - Prints an unsigned decimal number.
 * @n: Number to print.
 * @width: Minimum field width.
 * @precision: Minimum number of digits.
 * @precision_set: Whether precision was specified.
 * @zero_flag: Whether zero padding is active.
 * @left_flag: Whether left justification is active.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_unsigned(unsigned long int n, int width, int precision,int precision_set, int zero_flag, int left_flag,char *buffer, unsigned int *index)
{
    unsigned long int temp = n;
    int digits = 1;
    int zeros;
    int padding;
    int count = 0;
    int result;

    if (precision_set && precision == 0 && n == 0)
    {
        digits = 0;
    }
    else
    {
        while (temp >= 10)
        {
            temp /= 10;
            digits++;
        }
    }

    zeros = precision - digits;
    if (zeros < 0)
    {
        zeros = 0;
    }

    padding = width - digits - zeros;
    if (padding < 0)
    {
        padding = 0;
    }

    if (!left_flag)
    {
        result = print_padding(padding, 0, (zero_flag && !precision_set) ? '0' : ' ',buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_padding(zeros, 0, '0', buffer, index);
    if (result == -1)
    {
        return (-1);
    }
    count += result;

    if (digits > 0)
    {
        result = print_unsigned_digits(n, buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    if (left_flag)
    {
        result = print_padding(padding, 0, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    return (count);
}

/**
 * print_number - Prints a signed decimal number.
 * @n: Number to print.
 * @plus_flag: Whether to print a plus sign.
 * @space_flag: Whether to print a leading space.
 * @width: Minimum field width.
 * @precision: Minimum number of digits.
 * @precision_set: Whether precision was specified.
 * @zero_flag: Whether zero padding is active.
 * @left_flag: Whether left justification is active.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_number(long int n, int plus_flag, int space_flag, int width,int precision, int precision_set, int zero_flag,int left_flag, char *buffer, unsigned int *index)
{
    unsigned long int magnitude;
    unsigned long int temp;
    int digits = 1;
    int zeros;
    int sign_length = 0;
    int padding;
    int count = 0;
    int result;
    char sign = '\0';

    if (n < 0)
    {
        sign = '-';
        magnitude = 0UL - (unsigned long int)n;
    }
    else
    {
        magnitude = (unsigned long int)n;
        if (plus_flag)
        {
            sign = '+';
        }
        else if (space_flag)
        {
            sign = ' ';
        }
    }

    if (sign != '\0')
    {
        sign_length = 1;
    }

    if (precision_set && precision == 0 && magnitude == 0)
    {
        digits = 0;
    }
    else
    {
        temp = magnitude;
        while (temp >= 10)
        {
            temp /= 10;
            digits++;
        }
    }

    zeros = precision - digits;
    if (zeros < 0)
    {
        zeros = 0;
    }

    padding = width - sign_length - digits - zeros;
    if (padding < 0)
    {
        padding = 0;
    }

    if (!left_flag && !(zero_flag && !precision_set))
    {
        result = print_padding(padding, 0, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    if (sign != '\0')
    {
        if (print_char(sign, buffer, index) == -1)
        {
            return (-1);
        }
        count++;
    }

    if (!left_flag && zero_flag && !precision_set)
    {
        result = print_padding(padding, 0, '0', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_padding(zeros, 0, '0', buffer, index);
    if (result == -1)
    {
        return (-1);
    }
    count += result;

    if (digits > 0)
    {
        result = print_unsigned_digits(magnitude, buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    if (left_flag)
    {
        result = print_padding(padding, 0, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    return (count);
}
