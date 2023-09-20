#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
		return (-1);
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
	} while (c != EOF);
	if (cmd != NULL)
		free(cmd);
	fclose(f_ptr);
	free_stack(head);
	return (0);
}

void add_c(char **s, char c)
{
	unsigned int len_s = 0;
	char *tmp_p;

	if (!(*s))
	{
		*s = malloc(sizeof(char) * 2);
		(*s)[0] = c;
		(*s)[1] = '\0';
		return;
	}
	tmp_p = *s;
	len_s = strlen(*s);

	(*s) = malloc(sizeof(char) * (len_s + 2));
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
		printf(":_( - Error occured at line %u\n", l_nr);
	else if (res == 0)
		printf(":( - %s at line %u failed\n", op, l_nr);
	else
		printf(":) - %s at line %u executed successfully\n", op, l_nr);
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
