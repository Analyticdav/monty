#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ERRORNO = 1;

int read_file(const char *filepath)
{
	FILE *f_ptr;
	char c;
	char *cmd = NULL;
	unsigned int l_nr = 1;
	stack_t *head;

	head = NULL;
	f_ptr = fopen(filepath, "rb");
	if (f_ptr == NULL)
	{
		error_handler(1, NULL, NULL, filepath, NULL, NULL);
	}
	do {
		c = fgetc(f_ptr);
		if (c != ' ' && c != '\n')
			add_c(&cmd, c);
		if (c == '\n' && cmd != NULL)
		{
			handle_op(cmd, l_nr, &head);
			free(cmd);
			cmd = NULL;
			l_nr++;
		}
	} while (c != EOF && ERRORNO != -1);
	if (cmd != NULL)
		free(cmd);
	fclose(f_ptr);
	free_stack(head);
	if (ERRORNO == -1)
		exit(EXIT_FAILURE);
	return (0);
}

void add_c(char **s, char c)
{
	unsigned int len_s = 0;
	char *tmp_p;

	if (!(*s))
	{
		*s = malloc(sizeof(char) * 2);
		if ((*s) == NULL)
			error_handler(4, NULL, NULL, NULL, NULL, NULL);
		(*s)[0] = c;
		(*s)[1] = '\0';
		return;
	}
	tmp_p = *s;
	len_s = strlen(*s);

	(*s) = malloc(sizeof(char) * (len_s + 2));
	if ((*s) == NULL)
		error_handler(4, NULL, NULL, NULL, NULL, NULL);
	strcpy(*s, tmp_p);
	(*s)[len_s] = c;
	(*s)[len_s + 1] = '\0';

	free(tmp_p);
}

void handle_op(char *op, unsigned int l_nr, stack_t **stack)
{
	int res = 0;

	res = chk_op(op, stack, l_nr);
	if (res < 0)
		error_handler(5, *stack, NULL, NULL, &l_nr, op);
	else if (res == 0)
		error_handler(2, *stack, NULL, NULL, &l_nr, op);
}

int get_args(char *arg)
{
	int arg_i = 0;

	if (*arg == '\0')
		return (-1);
	if (*arg == '0')
		return (0);
	arg_i = atoi(arg);
	if (arg_i == 0)
		return (-2);
	return (arg_i);
}

void error_handler(
	int ERRNO,
	stack_t *stack,
	FILE *f_stream,
	const char *file_name,
	unsigned int *line_no,
	char *op_code
)
{
	(void) ERRNO,
	(void) stack,
	(void) f_stream,
	(void) file_name,
	(void) line_no,
	(void) op_code;

	switch (ERRNO)
	{
		case 1:
			fprintf(stderr, "Error: can't open file %s\n", file_name);
			break;
		case 2:
			fprintf(stderr, "L:%i unknown instruction %s\n", *line_no, op_code);
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
		default:
			fprintf(stderr, "An error occured\n");
			break;
	}
	ERRORNO = -1;
}
