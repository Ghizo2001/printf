#include "main.h"
void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - produces output according to a format
 * @format: a character string
 * Return:  the number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	{
		return (-1);
	}
	va_start(args, format);

	for (i = 0; format && format[0] != '\0'; i++)
	{
		if (format[0] != '%')
		{
			buffer[buff_ind++] = format[i];

			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind);
			}
			printed_chars++;
		}
		else
		{
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			i++;
			printed = handle_print(format, &i, args, buffer,
					flags, width, precision, size);
			if (printed == -1)
			{
				return (-1);
			}
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(args);
	return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
