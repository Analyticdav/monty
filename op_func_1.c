#include "monty.h"
#include <stdio.h>
#include <string.h>

static int op_arg;

int chk_op(char *op, stack_t **stack, int l_nr)
{
	int i = 0, arg = 0;
	int j, cnt = 0;
	instruction_t allowed_ops[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};

	while (op[i] != '\0')
	{
		if (op[i] == ' ')
			break;
		i++;
	}
	for (j = 0; allowed_ops[j].opcode != NULL; j++)
	{
		for (cnt = 0; cnt < i; cnt++)
		{
			if (allowed_ops[j].opcode[cnt] != op[cnt])
				break;
			cnt++;
		}
		if (cnt == i)
		{
			arg = get_args(op);
			if (arg >= 0)
				op_arg = arg;
			else if (strcmp(allowed_ops[j].opcode, "push") == 0 && arg < 0)
				return (-1);
			allowed_ops[j].f(stack, l_nr);
			return (1);
		}
	}
	return (0);
}
void push(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	add_snodeint_end(stack, op_arg);
}

void pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	if ((*stack) == NULL)
		return;
	print_stack(*stack);
}
void pop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
void swap(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
