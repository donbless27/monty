#include <stdlib.h>

char **strtow(char *str, char *delims);
int is_delim(char ch, char *delims);
int get_word_length(char *str, char *delims);
int get_word_count(char *str, char *delims);
char *get_next_word(char *str, char *delims);

/**
 * strtow - takes a string and seperates words
 * @str: the string to seperate into words
 * @delims: delimitors to use to delimit words
 * Return: 2D array of pointers to each word
 */

char **strtow(char *str, char *delims)
{
	char **words = NULL;
	int w_count, wordLen, n, k = 0;

	if (str == NULL || !*str)
		return (NULL);
	w_count = get_word_count(str, delims);


	if (w_count == 0)
		return (NULL);
	words = malloc((w_count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	while (k < w_count)
	{
		wordLen = get_word_length(str, delims);
		if (is_delim(*str, delims))
		{
			str = get_next_word(str, delims);
		}
		words[k] = malloc((wordLen + 1) * sizeof(char));
		if (words[k] == NULL)
		{
			while (k >= 0)
			{
				k--;
				free(words[i]);
			}
			free(words);
			return (NULL);
		}
		n = 0;
		while (n < wordLen)
		{
			words[k][n] = *(str + n);
			n++;
		}
		words[k][n] = '\0';
		str = get_next_word(str, delims);
		k++;
	}
	words[k] = NULL;
	return (words);
}

/**
 * is_delim - checks if stream has delimitor char
 * @ch: character in stream
 * @delims: null terminated array of delimitors
 * Return: 1 success, 0 failure
 */

int is_delim(char ch, char *delims)
{
	int k = 0;

	while (delims[k])
	{
		if (delims[k] == ch)
			return (1);
		k++;
	}
	return (0);
}

/**
 * get_word_length - to gets the word length
 *  of current word in string
 * @str: string to get word length from current word
 * @delims: use to delimit words
 * Return: word length of current word
 */

int get_word_length(char *str, char *delims)
{
	int w_Len = 0, pending = 1, k = 0;

	while (*(str + k))
	{
		if (is_delim(str[k], delims))
			pending = 1;
		else if (pending)
		{
			w_Len++;
		}
		if (w_Len > 0 && is_delim(str[k], delims))
			break;
		k++;
	}
	return (w_Len);
}

/**
 * get_word_count - to gets the word count of a string
 * @str: the string to get word count from
 * @delims: use to delimit words
 * Return: word count
 */

int get_word_count(char *str, char *delims)
{
	int w_count = 0, pending = 1, k = 0;

	while (*(str + k))
	{
		if (is_delim(str[k], delims))
			pending = 1;
		else if (pending)
		{
			pending = 0;
			w_count++;
		}
		k++;
	}
	return (w_count);
}

/**
 * get_next_word - to gets the next word in a string
 * @str: the string to get next word from
 * @delims: To delimit words
 * Return: pointer to first char of next word
 */

char *get_next_word(char *str, char *delims)
{
	int pending = 0;
	int n = 0;

	while (*(str + n))
	{
		if (is_delim(str[n], delims))
			pending = 1;
		else if (pending)
			break;
		n++;
	}
	return (str + n);
}
