#include "main.h"

/**
 * get_size - Calculate the size for argument casting
 * @format: Formatted string for printing arguments
 * @i: Current index in the format string
 *
 * Return: Size value
 */
int get_size(const char *format, int *i)
{
	int size = 0;
	int curr_i = *i + 1;

	if (format[curr_i] == 'l')
	{
		size = S_LONG;
	}
	else if (format[curr_i] == 'h')
	{
		size = S_SHORT;
	}

	if (size == 0)
	{
		*i = curr_i - 1;
	}
	else
	{
		*i = curr_i;
	}

	return (size);
}
