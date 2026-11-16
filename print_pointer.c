#include "main.h"

/**
 * print_address - Prints an address in hexadecimal.
 * @n: Address to print.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
static int print_address(unsigned long int n, char *buffer,unsigned int *index)
{
    char *digits = "0123456789abcdef";
    int count = 0;
    int result;

    if (n >= 16)
    {
        result = print_address(n / 16, buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_char(digits[n % 16], buffer, index);
    if (result == -1)
    {
        return (-1);
    }

    return (count + result);
}

/**
 * print_pointer - Prints a pointer address.
 * @ptr: Pointer to print.
 * @width: Minimum field width.
 * @zero_flag: Whether zero padding is active.
 * @left_flag: Whether left justification is active.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_pointer(void *ptr, int width, int zero_flag, int left_flag,char *buffer, unsigned int *index)
{
    unsigned long int address;
    unsigned long int temp;
    int digits = 1;
    int padding;
    int count = 0;
    int result;

    if (ptr == NULL)
    {
        return (print_string("(nil)", width, 0, 0, left_flag,buffer, index));
    }

    address = (unsigned long int)ptr;
    temp = address;

    while (temp >= 16)
    {
        temp /= 16;
        digits++;
    }

    padding = width - digits - 2;
    if (padding < 0)
    {
        padding = 0;
    }

    if (!left_flag && !zero_flag)
    {
        result = print_padding(padding, 0, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    if (print_char('0', buffer, index) == -1 ||
        print_char('x', buffer, index) == -1)
    {
        return (-1);
    }
    count += 2;

    if (!left_flag && zero_flag)
    {
        result = print_padding(padding, 0, '0', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    result = print_address(address, buffer, index);
    if (result == -1)
    {
        return (-1);
    }
    count += result;

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
