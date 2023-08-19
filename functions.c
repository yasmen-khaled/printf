#include "main.h"

/**
 * print_char - printing char
 * @types: List
 *
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: chars printed
 */


/**** %c  ***/
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/* %s */


/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates
 * @width:width.
 * @precision: Precision
 * @size: Size
 * Return: Number of chars printed
 */



int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = 0, x;
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

	while (s[l] != '\0')
		l++;

	if (precision >= 0 && precision < l)
		l = precision;

	if (width > l)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], l);
			for (x = width - l; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - l; x > 0; x--)
				write(1, " ", 1);
			write(1, &s[0], l);
			return (width);
		}
	}

	return (write(1, s, l));
}


/** %% */

/**
 * print_percent - Prints a percent
 * @types:arguments
 * @buffer: Buffer array to handle print
 * @flags: Calcuait
 * @width:width.
 * @precision: Precision specification
 * @size: Size
 * Return: numbers of chars that printied
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

/* %i */

/**
 * print_int - Print int
 * @types: arguments
 * @buffer: Buffer array
 * @flags: Calculates
 *
 * @width: width.
 *
 * @precision: Precision
 *
 * @size: Size specifier
 * Return: Number of chars printed
 */


int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}


/* binary */


/**
 * print_binary - Prints
 * @types: Lista of arguments
 * @buffer: Buffer
 * @flags:  Calculates
 * @width: get width.
 * @precision: Precisions
 * @size: Size specifier
 * Return: c
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, m, i, sum;
	unsigned int a[32];
	int c;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = x / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (x / m) % 2;
	}
	for (i = 0, sum = 0, c = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}
