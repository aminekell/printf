#include "main.h"

/**
 * get_flags - Determine active formatting flags
 * @format: Formatted string containing print specifications
 * @i: Current index in the format string
 *
 * Return: Calculated flags value
 */
int get_flags(const char *format, int *i)
{
	int flags = 0;
	int curr_i = *i + 1;
	const char FLAGS_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	while (format[curr_i] != '\0')
	{
		int j;

		for (j = 0; FLAGS_CHARS[j] != '\0'; j++)
		{
			if (format[curr_i] == FLAGS_CHARS[j])
			{
				flags |= FLAGS_VALUES[j];
				break;
			}
		}
		if (FLAGS_CHARS[j] == '\0')
		{
			break;
		}
		curr_i++;
	}

	*i = curr_i - 1;

	return (flags);
}
