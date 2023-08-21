#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @c: The character to be evaluated
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appends ASCII in hexadecimal code to buffer
 * @buffer: The array of characters
 * @i: The index at which to start appending
 * @ascii_code: The ASCII code to append
 *
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks if a character is a digit
 * @c: The character to be evaluated
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Converts a number to the specified size
 * @num: The number to be casted
 * @size: The size indicator for casting
 *
 * Return: The casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short) num);

	return ((int) num);
}

/**
 * convert_size_unsgnd - Converts an unsigned number to the specified size
 * @num: The number to be casted
 * @size: The size indicator for casting
 *
 * Return: The casted value of num
 */
unsigned long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short) num);

	return ((unsigned int) num);
}
