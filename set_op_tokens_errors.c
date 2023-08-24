#include "monty.h"

/**
 * set_op_tok_error - sets last element of op_toks as an error code.
 * @error_code: integer to store as a string in op_toks.
 */

void set_op_tok_error(int error_code)
{
	int tokens_len = 0, k = 0;
	char *exit_str = NULL;
	char **new_toks = NULL;

	tokens_len = token_arr_len();
	new_toks = malloc(sizeof(char *) * (tokens_len + 2));
	if (!op_toks)
	{
		malloc_error();
		return;
	}
	while (k < tokens_len)
	{
		new_toks[k] = op_toks[k];
		k++;
	}
	exit_str = get_int(error_code);
	if (!exit_str)
	{
		free(new_toks);
		malloc_error();
		return;
	}
	new_toks[k++] = exit_str;
	new_toks[k] = NULL;
	free(op_toks);
	op_toks = new_toks;
}
