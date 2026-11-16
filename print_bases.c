#include "main.h"

/**
 * print_base_digits - Prints a number in a selected base.
 * @n: Number to print.
 * @base: Number base.
 * @uppercase: Whether alphabetic digits are uppercase.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
static int print_base_digits(unsigned long int n, unsigned int base,
                             int uppercase, char *buffer,
                             unsigned int *index)
{
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int count = 0;
    int result;

    if (n >= base)
    {
        result = print_base_digits(n / base, base, uppercase,
                                   buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_char(digits[n % base], buffer, index);
    if (result == -1)
    {
        return (-1);
    }

    return (count + result);
}

/**
 * print_base - Prints a number in a selected base.
 * @n: Number to print.
 * @base: Number base.
 * @uppercase: Whether alphabetic digits are uppercase.
 * @prefix: Optional prefix.
 * @width: Minimum field width.
 * @precision: Minimum number of digits.
 * @precision_set: Whether precision was specified.
 * @zero_flag: Whether zero padding is active.
 * @left_flag: Whether left justification is active.
 * @hash_octal: Whether octal alternate form is active.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
static int print_base(unsigned long int n, unsigned int base,int uppercase, char *prefix, int width,int precision, int precision_set, int zero_flag,int left_flag, int hash_octal, char *buffer,unsigned int *index)
{
    unsigned long int temp = n;
    int digits = 1;
    int zeros;
    int prefix_length = 0;
    int padding;
    int count = 0;
    int result;

    if (precision_set && precision == 0 && n == 0)
    {
        digits = 0;
    }
    else
    {
        while (temp >= base)
        {
            temp /= base;
            digits++;
        }
    }

    zeros = precision - digits;
    if (zeros < 0)
    {
        zeros = 0;
    }

    if (hash_octal && ((n == 0 && digits == 0) ||
                       (n != 0 && zeros == 0)))
    {
        prefix = "0";
    }

    if (prefix != NULL)
    {
        while (prefix[prefix_length] != '\0')
        {
            prefix_length++;
        }
    }

    padding = width - prefix_length - digits - zeros;
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

    if (prefix != NULL)
    {
        while (*prefix != '\0')
        {
            if (print_char(*prefix, buffer, index) == -1)
            {
                return (-1);
            }
            prefix++;
            count++;
        }
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
        result = print_base_digits(n, base, uppercase, buffer, index);
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
 * print_binary - Prints an unsigned number in binary.
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
int print_binary(unsigned long int n, int width, int precision,int precision_set, int zero_flag, int left_flag,char *buffer, unsigned int *index)
{
    return (print_base(n, 2, 0, NULL, width, precision, precision_set,zero_flag, left_flag, 0, buffer, index));
}

/**
 * print_octal - Prints an unsigned number in octal.
 * @n: Number to print.
 * @hash_flag: Whether alternate form is active.
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
int print_octal(unsigned long int n, int hash_flag, int width,int precision, int precision_set, int zero_flag,int left_flag, char *buffer, unsigned int *index)
{
    return (print_base(n, 8, 0, NULL, width, precision, precision_set,zero_flag, left_flag, hash_flag, buffer, index));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal.
 * @n: Number to print.
 * @uppercase: Whether alphabetic digits are uppercase.
 * @hash_flag: Whether alternate form is active.
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
int print_hexadecimal(unsigned long int n, int uppercase, int hash_flag,int width, int precision, int precision_set,int zero_flag, int left_flag, char *buffer,unsigned int *index)
{
    char *prefix = NULL;

    if (hash_flag && n != 0)
    {
        prefix = uppercase ? "0X" : "0x";
    }

    return (print_base(n, 16, uppercase, prefix, width, precision,precision_set, zero_flag, left_flag, 0,buffer, index));
}
