#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ERRORNO = 1;
/**
 * read_file - Read and parse a file containing stack operations.
 *
 * This function reads and parses a file specified by `filepath`. It reads
 * and processes lines containing stack operations, executing them on a stack
 * as defined by the stack manipulation program. The function handles errors,
 * including file not found, and provides informative error messages.
 *
 * @filepath: The path to the file to be read and parsed.
 *
 * Return: 0 on success, or exits with a failure status on error.
 */
int read_file(const char *filepath)
{
	FILE *f_ptr;
	char c, *cmd = NULL;
	unsigned int l_nr = 1, cmd_flag = 0;
	stack_t *head;

	head = NULL;
	f_ptr = fopen(filepath, "rb");
	if (f_ptr == NULL)
	{
		error_handler(1, NULL, NULL, filepath, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	do {
		c = fgetc(f_ptr);
		if (c != '\n')
		{
			if (c == ' ' && cmd_flag)
			{
				add_c(&cmd, ' ');
				cmd_flag = 0;
			}
			if (c != ' ')
			{
				add_c(&cmd, c);
				cmd_flag = 1;
			}
		}
		if (c == '\n' && cmd != NULL)
		{
			handle_op(cmd, l_nr, &head);
			free(cmd);
			cmd = NULL;
			cmd_flag = 0;
			l_nr++;
		}
	} while (c != EOF && ERRORNO != -1);
	clean_up(f_ptr, cmd, head);
	return (0);
}
/**
 * add_c - Append a character to a dynamically allocated string.
 *
 * This function appends the character `c` to the end of the dynamically
 * allocated string `*s`. If `*s` is NULL, it allocates memory for a new
 * string and assigns `c` to it. If memory allocation fails, it calls the
 * error_handler function with error code 4.
 *
 * @s: A pointer to a pointer to the string.
 * @c: The character to append to the string.
 */
void add_c(char **s, char c)
{
	unsigned int len_s = 0;
	char *tmp_p;

	if (!(*s))
	{
		*s = malloc(sizeof(char) * 2);
		if ((*s) == NULL)
		{
			error_handler(4, NULL, NULL, NULL, NULL, NULL);
			return;
		}
		(*s)[0] = c;
		(*s)[1] = '\0';
		return;
	}
	tmp_p = *s;
	len_s = strlen(*s);

	(*s) = malloc(sizeof(char) * (len_s + 2));
	if ((*s) == NULL)
	{
		error_handler(4, NULL, NULL, NULL, NULL, NULL);
		return;
	}
	strcpy(*s, tmp_p);
	(*s)[len_s] = c;
	(*s)[len_s + 1] = '\0';

	free(tmp_p);
}
/**
 * clean_up - Free allocated resources and close file.
 *
 * This function is responsible for cleaning up allocated resources and
 * closing a file stream. It frees the memory pointed to by `cmd`, frees
 * the stack using `free_stack`, and closes the file pointed to by `file_p`.
 * Additionally, it checks if the global variable `ERRORNO` is set to -1, and
 * if so, it exits with EXIT_FAILURE.
 *
 * @file_p: A pointer to the file stream.
 * @cmd: A pointer to a dynamically allocated string.
 * @stack: A pointer to a stack.
 */
void clean_up(FILE *file_p, char *cmd, stack_t *stack)
{
	if (cmd != NULL)
		free(cmd);
	fclose(file_p);
	free_stack(stack);
	if (ERRORNO == -1)
		exit(EXIT_FAILURE);
}

/**
 * get_arg - Get argument from opcode.
 *
 * This function extracts the argument from an opcode string. It tokenizes
 * the opcode and returns the argument as a string. If no argument is found,
 * it returns "NO_ARG." If the argument is invalid (contains non-numeric
 * characters), it returns "INVALID_ARG."
 *
 * @opcode: The opcode string.
 *
 * Return: The argument as a string or "NO_ARG" or "INVALID_ARG."
 */
char *get_arg(char *opcode)
{
	char *token;
	int i, is_negative = 0;

	token = strtok(opcode, " ");
	token = strtok(NULL, " ");

	if (token == NULL)
		return ("NO_ARG");

	if (*token == '-')
		is_negative = 1;

	for (i = is_negative ? 1 : 0; token[i] != '\0'; i++)
		if (!(token[i] > 47 && token[i] < 58))
			return ("INVALID_ARG");
	return (token);
}
/**
 * error_handler - Handle errors and print error messages.
 *
 * This function handles different types of errors and prints corresponding
 * error messages to stderr. It takes an error code `ERRNO` and additional
 * parameters depending on the error type. It uses the global variable
 * `ERRORNO` to control program termination.
 *
 * @ERRNO: The error code indicating the type of error.
 * @stack: A pointer to a stack.
 * @f_stream: A pointer to a file stream.
 * @file_name: The name of the file causing the error.
 * @line_no: A pointer to the line number where the error occurred.
 * @op_code: The opcode causing the error.
 */
void error_handler(
	int ERRNO,
	stack_t *stack,
	FILE *f_stream,
	const char *file_name,
	unsigned int *line_no,
	char *op_code
)
{
	(void) stack, (void) f_stream, (void) file_name,
	(void) line_no, (void) op_code;

	switch (ERRNO)
	{
		case 1:
			fprintf(stderr, "Error: can't open file %s\n", file_name);
			break;
		case 2:
			fprintf(stderr, "L%i: unknown instruction %s\n", *line_no, op_code);
			break;
		case 3:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%i: usage: push integer\n", *line_no);
			break;
		case 6:
			fprintf(stderr, "L%i: can't %s, stack empty\n", *line_no, op_code);
			break;
		case 7:
			fprintf(stderr, "L%i: can't %s, stack too short\n", *line_no, op_code);
			break;
		case 8:
			fprintf(stderr, "L%i: can't %s, stack empty\n", *line_no, op_code);
			break;
		case 9:
			fprintf(stderr, "L%i: division by zero\n", *line_no);
			break;
		case 10:
			fprintf(stderr, "L%i: can't %s an empty stack\n", *line_no, op_code);
			break;
	}
	ERRORNO = -1;
}
