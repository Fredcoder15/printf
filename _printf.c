#include "main.h"

/**
 * _printf - Produces output according to a format.
 * @format: Format string.
 *
 * Return: Number of characters printed, or -1 on failure.
 */
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[1024];
    unsigned int index = 0;
    int count = 0;
    int result;
    int width;
    int precision;
    int precision_set;
    int plus_flag;
    int space_flag;
    int hash_flag;
    int zero_flag;
    int left_flag;
    char length;
    char spec;

    if (format == NULL)
    {
        return (-1);
    }

    va_start(args, format);

    while (*format != '\0')
    {
        if (*format != '%')
        {
            result = print_char(*format, buffer, &index);
            if (result == -1)
            {
                va_end(args);
                return (-1);
            }

            count += result;
            format++;
            continue;
        }

        format++;

        if (*format == '\0')
        {
            break;
        }

        plus_flag = 0;
        space_flag = 0;
        hash_flag = 0;
        zero_flag = 0;
        left_flag = 0;
        width = 0;
        precision = 0;
        precision_set = 0;
        length = '\0';

        while (*format == '+' || *format == ' ' || *format == '#' ||
               *format == '0' || *format == '-')
        {
            if (*format == '+')
            {
                plus_flag = 1;
            }
            else if (*format == ' ')
            {
                space_flag = 1;
            }
            else if (*format == '#')
            {
                hash_flag = 1;
            }
            else if (*format == '0')
            {
                zero_flag = 1;
            }
            else if (*format == '-')
            {
                left_flag = 1;
            }

            format++;
        }

        while (*format >= '0' && *format <= '9')
        {
            width = width * 10 + (*format - '0');
            format++;
        }

        if (*format == '.')
        {
            precision_set = 1;
            format++;

            while (*format >= '0' && *format <= '9')
            {
                precision = precision * 10 + (*format - '0');
                format++;
            }
        }

        if (*format == 'l' || *format == 'h')
        {
            length = *format;
            format++;
        }

        spec = *format;
        result = 0;

        switch (spec)
        {
            case 'c':
            {
                char c = (char)va_arg(args, int);

                if (!left_flag)
                {
                    result += print_padding(width, 1, ' ', buffer, &index);
                }

                if (result == -1 ||
                    print_char(c, buffer, &index) == -1)
                {
                    va_end(args);
                    return (-1);
                }

                count += result + 1;
                result = 0;

                if (left_flag)
                {
                    result = print_padding(width, 1, ' ', buffer, &index);
                    if (result == -1)
                    {
                        va_end(args);
                        return (-1);
                    }
                    count += result;
                }
                break;
            }

            case 's':
            {
                result = print_string(va_arg(args, char *), width,
                                      precision, precision_set, left_flag,
                                      buffer, &index);
                break;
            }

            case 'S':
            {
                result = print_special_string(va_arg(args, char *),
                                              width, buffer, &index);
                break;
            }

            case 'r':
            {
                result = print_reverse(va_arg(args, char *),
                                       buffer, &index);
                break;
            }

            case 'R':
            {
                result = print_rot13(va_arg(args, char *),
                                     buffer, &index);
                break;
            }

            case '%':
            {
                if (!left_flag)
                {
                    result = print_padding(width, 1, ' ', buffer, &index);
                    if (result == -1)
                    {
                        va_end(args);
                        return (-1);
                    }
                    count += result;
                }

                if (print_char('%', buffer, &index) == -1)
                {
                    va_end(args);
                    return (-1);
                }
                count++;

                if (left_flag)
                {
                    result = print_padding(width, 1, ' ', buffer, &index);
                    if (result == -1)
                    {
                        va_end(args);
                        return (-1);
                    }
                    count += result;
                }
                break;
            }

            case 'd':
            case 'i':
            {
                long int n;

                if (length == 'l')
                {
                    n = va_arg(args, long int);
                }
                else if (length == 'h')
                {
                    n = (short int)va_arg(args, int);
                }
                else
                {
                    n = va_arg(args, int);
                }

                result = print_number(n, plus_flag, space_flag, width,
                                     precision, precision_set, zero_flag,
                                     left_flag, buffer, &index);
                break;
            }

            case 'u':
            case 'b':
            case 'o':
            case 'x':
            case 'X':
            {
                unsigned long int n;

                if (length == 'l')
                {
                    n = va_arg(args, unsigned long int);
                }
                else if (length == 'h')
                {
                    n = (unsigned short int)va_arg(args, int);
                }
                else
                {
                    n = va_arg(args, unsigned int);
                }

                if (spec == 'u')
                {
                    result = print_unsigned(n, width, precision,
                                            precision_set, zero_flag,
                                            left_flag, buffer, &index);
                }
                else if (spec == 'b')
                {
                    result = print_binary(n, width, precision,
                                          precision_set, zero_flag,
                                          left_flag, buffer, &index);
                }
                else if (spec == 'o')
                {
                    result = print_octal(n, hash_flag, width, precision, precision_set, zero_flag, left_flag, buffer, &index);
                }
                else
                {
                    result = print_hexadecimal(n, spec == 'X',hash_flag, width, precision,precision_set, zero_flag,left_flag, buffer, &index);
                }
                break;
            }

            case 'p':
            {
                result = print_pointer(va_arg(args, void *), width,zero_flag, left_flag, buffer,&index);
                break;
            }

            default:
            {
                if (print_char('%', buffer, &index) == -1 ||
                    print_char(spec, buffer, &index) == -1)
                {
                    va_end(args);
                    return (-1);
                }

                count += 2;
                break;
            }
        }

        if (result == -1)
        {
            va_end(args);
            return (-1);
        }

        count += result;
        format++;
    }

    result = flush_buffer(buffer, &index);
    va_end(args);

    if (result == -1)
    {
        return (-1);
    }

    return (count);
}
