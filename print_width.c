#include "main.h"

/**
 * print_padding - Prints padding characters to meet field width.
 * @width: Minimum field width.
 * @printed: Number of characters already printed or reserved.
 * @pad: Character used for padding.
 * @buffer: Output buffer.
 * @index: Current buffer position.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int print_padding(int width, int printed, char pad, char *buffer,unsigned int *index)
{
    int count = 0;
    int result;

    while (count + printed < width)
    {
        result = print_char(pad, buffer, index);
        if (result == -1)
        {
            return (-1);
        }
        count += result;
    }

    return (count);
}
