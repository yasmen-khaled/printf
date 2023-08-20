
#include "main.h"

/**
 * get_width - Calculates
 * @format: Formatted string
 * @i: List of arguments
 * @list: list of arguments.
 *
 * Return: w
 */

int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int w = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			w *= 10;
			w += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (w);
}
