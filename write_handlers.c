#include "main.h"

int customHandleWriteChar(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char paddingChar = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddingChar = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = paddingChar;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

int customWriteNumber(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char paddingChar = ' ', extraChar = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (isNegative)
		extraChar = '-';
	else if (flags & F_PLUS)
		extraChar = '+';
	else if (flags & F_SPACE)
		extraChar = ' ';

	return (writeNum(index, buffer, flags, width, precision,
		length, paddingChar, extraChar));
}

int writeNum(int index, char buffer[],
	int flags, int width, int precision,
	int length, char paddingChar, char extraChar)
{
	int i, paddingStart = 1;

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = paddingChar = ' ';
	if (precision > 0 && precision < length)
		paddingChar = ' ';
	while (precision > length)
		buffer[--index] = '0', length++;
	if (extraChar != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddingChar == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0')
		{
			if (extraChar)
				buffer[--paddingStart] = extraChar;
			return (write(1, &buffer[paddingStart], i - paddingStart) +
				write(1, &buffer[index], length - (1 - paddingStart)));
		}
	}
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], length));
}

int writeUnsgnd(int isNegative, int index,
	char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char paddingChar = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = paddingChar;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

int writePointer(char buffer[], int index, int length,
	int width, int flags, char paddingChar, char extraChar, int paddingStart)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS)
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
