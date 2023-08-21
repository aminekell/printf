#include "main.h"
#include <stdarg.h>
/**
 * get_precision - Determine the precision for formatting
 * @format: Formatted string containing print specifications
 * @i: Current index in the format string
 * @list: List of arguments
 *
 * Return: Computed precision value
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
	{
		return (precision);
	}

	precision = 0;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
		curr_i++;
	}

	*i = curr_i - 1;

	return (precision);
}
