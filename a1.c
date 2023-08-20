#include "main.h"

/* CHAR %c **/

/**
 * print_char - Prints char
 * @types: arguments
 * @buffer: Buffer array 
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */


int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}




/* STRING %s **/

/**
 * print_string - Prints a string
 * @types: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */


int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, x;
	char *s = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}

	while (s[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], length);
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			write(1, &s[0], length);
			return (width);
		}
	}

	return (write(1, s, length));
}






/* PERCENT %% **/


/**
 * print_percent - Prints a percent sign
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  Calculates
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */


int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}




/* int %i */
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */




int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int in = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int x;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[in--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	x = (unsigned long int)n;

	if (n < 0)
	{
		x = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (x > 0)
	{
		buffer[in--] = (x % 10) + '0';
		x /= 10;
	}

	in++;

	return (write_number(is_negative, in, buffer, flags, width, precision, size));
}




/* BINARY  b */


/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */


int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, num, i, s;
	unsigned int a[32];
	int c;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	num = 2147483648; /* (2 ^ 31) */
	a[0] = x / num;
	for (i = 1; i < 32; i++)
	{
		num /= 2;
		a[i] = (x / num) % 2;
	}
	for (i = 0, s = 0, c = 0; i < 32; i++)
	{
		s += a[i];
		if (s || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}
