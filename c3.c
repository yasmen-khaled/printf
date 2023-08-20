#include "main.h"

/*POINTER */


/**
 * print_pointer - Prints pointer
 * @types:arguments
 * @buffer: Buffer array
 * @flags:  Calculates
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */


int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int i = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *a = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (a == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)a;

	while (num_addrs > 0)
	{
		buffer[i--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	i++;
	return (write_pointer(buffer, i, length,
		width, flags, padd, extra_c, padd_start));
}

/**  non printable **/


/**
 * print_non_printable - Prints ascii codes
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  Calculates
 * @width: get width
 * @precision: Precision
 * @size: Size
 * Return: Numbers
 */


int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, offset = 0;
	char *s = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		return (write(1, "(null)", 6));

	while (s[x] != '\0')
	{
		if (is_printable(s[x]))
			buffer[x + offset] = s[x];
		else
			offset += append_hexa_code(s[x], buffer, x + offset);

		x++;
	}

	buffer[x + offset] = '\0';

	return (write(1, buffer, x + offset));
}

/*revers -_-*/


/**
 * print_reverse - Prints reverse string.
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision
 * @size: Size
 * Return: Numbers
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *s;
	int x, c = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	s = va_arg(types, char *);

	if (s == NULL)
	{
		UNUSED(precision);

		s = ")Null(";
	}
	for (x = 0; s[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char z = s[x];

		write(1, &z, 1);
		c++;
	}
	return (c);
}



/*STRING IN ROT13 */



/**
 * print_rot13string - Print string in rot13
 * @types: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */


int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *s;
	unsigned int xx, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	s = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		s = "(AHYY)";
	for (xx = 0; s[xx]; xx++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == s[xx])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = s[xx];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
