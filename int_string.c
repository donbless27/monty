#include <stdlib.h>

char *get_int(int num);
unsigned int _abs(int);
int get_numbase_len(unsigned int num, unsigned int base);
void fill_numbase_buff(unsigned int num, unsigned int base,
		       char *buff, int buff_size);

/**
 * get_int - gets a character pointer to new string containing int
 * @num: number to convert to string
 * Return: character pointer and NULL if malloc fails.
 */

char *get_int(int num)
{
	unsigned int temp;
	int length = 0;
	long num_l = 0;
	char *ret;

	temp = _abs(num);
	length = get_numbase_len(temp, 10);

	if (num < 0 || num_l < 0)
		length++; /* negative sign */
	ret = malloc(length + 1); /* create new string */
	if (!ret)
		return (NULL);

	fill_numbase_buff(temp, 10, ret, length);
	if (num < 0 || num_l < 0)
		ret[0] = '-';

	return (ret);
}

/**
 * _abs - gets the absolute val of an integer
 * @i: integer to get absolute val
 * Return: unsigned integer abs rep of i
 */

unsigned int _abs(int i)
{
	if (i < 0)
		return (-(unsigned int)i);
	return ((unsigned int)i);
}

/**
 * get_numbase_len - gets length of buffer needed for an unsigned int
 * @num: number to get length needed 
 * @base: base of number used by buffer
 * Return: length of buffer needed but doesn't contain null bt
 */
int get_numbase_len(unsigned int num, unsigned int base)
{
	int l = 1; /* all numbers contain atleast one digit */

	while (num > base - 1)
	{
		l++;
		num /= base;
	}
	return (l);
}

/**
 * fill_numbase_buff - fills buffer with correct numbers up to base 36
 * @num: number to convert
 * @base: Base of number used in conversion, only works up to base 36
 * @buff: Fill buffer with result of conversion
 * @buff_size: Buffer size in bytes
 * Return: Always void
 */
void fill_numbase_buff(unsigned int num, unsigned int base,
			char *buff, int buff_size)
{
	int rem, k = buff_size - 1;

	buff[buff_size] = '\0';
	while (k >= 0)
	{
		rem = num % base;
		if (rem > 9)
			buff[k] = rem + 87;
		else
			buff[k] = rem + '0';
		num /= base;
		k--;
	}
}
