0x11. C - printf

This project is a custom implementation of the C standard library function "printf()".

The aim is to understand how formatted output works in C and how to handle different conversion specifiers, flags, field width, and precision.

Description

The "_printf()" function produces output according to a format string and returns the number of characters printed, excluding the null byte.

Supported Conversion Specifiers

- "%c" - Prints a character.
- "%s" - Prints a string.
- "%%" - Prints the percent sign.
- "%d" and "%i" - Prints signed integers.
- "%b" - Prints an unsigned integer in binary.
- "%u" - Prints an unsigned integer.
- "%o" - Prints an unsigned integer in octal.
- "%x" and "%X" - Prints hexadecimal numbers.
- "%S" - Prints a string with non-printable characters represented in hexadecimal.
- "%p" - Prints a memory address.
- "%r" - Prints a string in reverse.
- "%R" - Prints a string using ROT13.

The project also handles flags, length modifiers, field width, and precision.

Compilation

Compile the source files using:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c

Usage

Include "main.h" in your C file and call "_printf()":

#include "main.h"

int main(void)
{
    _printf("Hello, %s!\n", "world");
    _printf("Number: %d\n", 42);

    return (0);
}

Files

- "_printf.c" - Main printf function and format dispatcher.
- "main.h" - Header file containing function prototypes.
- "print_chars.c" - Character and string handling.
- "print_numbers.c" - Signed and unsigned integer handling.
- "print_bases.c" - Binary, octal, and hexadecimal conversions.
- "print_custom.c" - Custom conversion specifiers.
- "print_pointer.c" - Pointer conversion.
- "print_width.c" - Field width and padding.

Authors

- Akpan-fred, Promise Friday. 