#include "monty.h"
#include <string.h>

void free_tokens(void);
unsigned int token_arr_len(void);
int is_empty_line(char *line, char *delims);
void (*get_op_func(char *opcode))(stack_t**, unsigned int);
int run_monty(FILE *script_fd);

/**
 * free_tokens - frees the global op_toks array of strings.
 */

void free_tokens(void)
{
	size_t k = 0;

	if (op_toks == NULL)
		return;

	for (k = 0; op_toks[k]; k++)
		free(op_toks[k]);

	free(op_toks);
}

/**
 * token_arr_len - Gets the length of current op_toks.
 * Return: Length of current op_toks as integer
 */
unsigned int token_arr_len(void)
{
	unsigned int tok_len = 0;

	while (op_toks[tok_len])
		tok_len++;
	return (tok_len);
}

/**
 * is_empty_line - Checks if a line read from getline only contains delimiters.
 * @line: pointer to the line.
 * @delims: string of delimiter characters.
 * Return: -1 If the line only contains delimiters
 *  Otherwise - 0.
 */
int is_empty_line(char *line, char *delims)
{
	int k, j;

	for (k = 0; line[k]; k++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[k] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * get_op_func - Matches an opcode with its corresponding function.
 * @opcode: The opcode to match
 * Return: pointer to the function.
 */
void (*get_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", monty_push},
		{"pall", monty_pall},
		{"pint", monty_pint},
		{"pop", monty_pop},
		{"swap", monty_swap},
		{"add", monty_add},
		{"nop", monty_nop},
		{"sub", monty_sub},
		{"div", monty_div},
		{"mul", monty_mul},
		{"mod", monty_mod},
		{"pchar", monty_pchar},
		{"pstr", monty_pstr},
		{"rotl", monty_rotl},
		{"rotr", monty_rotr},
		{"stack", monty_stack},
		{"queue", monty_queue},
		{NULL, NULL}
	};
	int k;

	for (k = 0; op_funcs[k].opcode; k++)
	{
		if (strcmp(opcode, op_funcs[k].opcode) == 0)
			return (op_funcs[k].f);
	}

	return (NULL);
}

/**
 * run_monty - primary function to execute a Monty bytecodes script
 * @script_fd: fFile descriptor for an open Monty bytecodes script
 * Return: EXIT_SUCCESS on success, error code on failure
 */
int run_monty(FILE *script_fd)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_len = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (init_stack(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, script_fd) != -1)
	{
		line_number++;
		op_toks = strtow(line, DELIMS);
		if (op_toks == NULL)
		{
			if (is_empty_line(line, DELIMS))
				continue;
			free_stack(&stack);
			return (malloc_error());
		}
		else if (op_toks[0][0] == '#') /* comment line */
		{
			free_tokens();
			continue;
		}
		op_func = get_op_func(op_toks[0]);
		if (op_func == NULL)
		{
			free_stack(&stack);
			exit_status = unknown_op_error(op_toks[0], line_number);
			free_tokens();
			break;
		}
		prev_tok_len = token_arr_len();
		op_func(&stack, line_number);
		if (token_arr_len() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			free_tokens();
			break;
		}
		free_tokens();
	}
	free_stack(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (malloc_error());
	}

	free(line);
	return (exit_status);
}
