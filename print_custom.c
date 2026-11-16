#include "main.h"

/**
 * print_special_string - Prints a string with escaped characters.
 * @str: String to print.
 * @width: Minimum field width.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_special_string(char *str, int width, char *buffer,unsigned int *index)
{
    char *hex = "0123456789ABCDEF";
    int length = 0;
    int count = 0;
    int result;
    unsigned char c;

    if (str == NULL)
    {
        str = "(null)";
    }

    while (str[length] != '\0')
    {
        length++;
    }

    for (result = 0; result < length; result++)
    {
        c = (unsigned char)str[result];

        if (c < 32 || c >= 127)
        {
            count += 4;
        }
        else
        {
            count++;
        }
    }

    result = print_padding(width, count, ' ', buffer, index);
    if (result == -1)
    {
        return (-1);
    }

    count = result;

    for (result = 0; str[result] != '\0'; result++)
    {
        c = (unsigned char)str[result];

        if (c < 32 || c >= 127)
        {
            if (print_char('\\', buffer, index) == -1 ||
                print_char('x', buffer, index) == -1 ||
                print_char(hex[c / 16], buffer, index) == -1 ||
                print_char(hex[c % 16], buffer, index) == -1)
            {
                return (-1);
            }
            count += 4;
        }
        else
        {
            if (print_char(c, buffer, index) == -1)
            {
                return (-1);
            }
            count++;
        }
    }

    return (count);
}

/**
 * print_reverse - Prints a string in reverse order.
 * @str: String to reverse.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_reverse(char *str, char *buffer, unsigned int *index)
{
    int length = 0;
    int count = 0;

    if (str == NULL)
    {
        str = "(null)";
    }

    while (str[length] != '\0')
    {
        length++;
    }

    while (length > 0)
    {
        length--;

        if (print_char(str[length], buffer, index) == -1)
        {
            return (-1);
        }
        count++;
    }

    return (count);
}

/**
 * print_rot13 - Prints a string using ROT13.
 * @str: String to convert.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_rot13(char *str, char *buffer, unsigned int *index)
{
    int count = 0;
    char c;

    if (str == NULL)
    {
        str = "(null)";
    }

    while (*str != '\0')
    {
        c = *str;

        if (c >= 'a' && c <= 'z')
        {
            c = ((c - 'a' + 13) % 26) + 'a';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c = ((c - 'A' + 13) % 26) + 'A';
        }

        if (print_char(c, buffer, index) == -1)
        {
            return (-1);
        }

        count++;
        str++;
    }

    return (count);
}
