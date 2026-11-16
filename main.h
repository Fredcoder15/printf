#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>

int _printf(const char *format, ...);
int flush_buffer(char *buffer, unsigned int *index);
int print_char(char c, char *buffer, unsigned int *index);

int print_string(char *str, int width, int precision,int precision_set, int left_flag,char *buffer, unsigned int *index);

int print_special_string(char *str, int width,char *buffer, unsigned int *index);

int print_reverse(char *str, char *buffer, unsigned int *index);
int print_rot13(char *str, char *buffer, unsigned int *index);

int print_number(long int n, int plus_flag, int space_flag, int width,int precision, int precision_set, int zero_flag,int left_flag, char *buffer, unsigned int *index);

int print_unsigned(unsigned long int n, int width, int precision,int precision_set, int zero_flag, int left_flag,char *buffer, unsigned int *index);

int print_binary(unsigned long int n, int width, int precision,int precision_set, int zero_flag, int left_flag,char *buffer, unsigned int *index);

int print_octal(unsigned long int n, int hash_flag, int width,int precision, int precision_set, int zero_flag, int left_flag, char *buffer, unsigned int *index);

int print_hexadecimal(unsigned long int n, int uppercase, int hash_flag,int width, int precision, int precision_set,int zero_flag, int left_flag, char *buffer,unsigned int *index);

int print_pointer(void *ptr, int width, int zero_flag, int left_flag,char *buffer, unsigned int *index);

int print_padding(int width, int printed, char pad,char *buffer, unsigned int *index);

#endif
