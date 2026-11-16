#include <unistd.h>
#include "main.h"

/**
 * flush_buffer - Writes the buffer contents to stdout.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters written, or -1 on failure.
 */
int flush_buffer(char *buffer, unsigned int *index)
{
    unsigned int total = 0;
    ssize_t written;

    while (total < *index)
    {
        written = write(1, buffer + total, *index - total);
        if (written <= 0)
        {
            return (-1);
        }
        total += written;
    }

    *index = 0;
    return (total);
}

/**
 * print_char - Adds a character to the output buffer.
 * @c: Character to print.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: 1 on success, or -1 on failure.
 */
int print_char(char c, char *buffer, unsigned int *index)
{
    buffer[*index] = c;
    (*index)++;

    if (*index == 1024)
    {
        if (flush_buffer(buffer, index) == -1)
        {
            return (-1);
        }
    }

    return (1);
}

/**
 * print_string - Prints a string with width and precision.
 * @str: String to print.
 * @width: Minimum field width.
 * @precision: Maximum number of characters.
 * @precision_set: Whether precision was specified.
 * @left_flag: Whether left justification is active.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_string(char *str, int width, int precision,int precision_set, int left_flag,char *buffer, unsigned int *index)
{
    int length = 0;
    int count = 0;
    int i;
    int result;

    if (str == NULL)
    {
        str = "(null)";
    }

    while (str[length] != '\0')
    {
        length++;
    }

    if (precision_set && precision < length)
    {
        length = precision;
    }

    if (!left_flag)
    {
        result = print_padding(width, length, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    for (i = 0; i < length; i++)
    {
        if (print_char(str[i], buffer, index) == -1)
        {
            return (-1);
        }
        count++;
    }

    if (left_flag)
    {
        result = print_padding(width, length, ' ', buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    return (count);
}
