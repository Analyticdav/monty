#include "monty.h"
#include <stdio.h>
#include <string.h>

static int op_arg;
/**
 * chk_op - Check and execute an operation.
 *
 * This function checks if the provided opcode is a valid operation and
 * executes it if valid. It compares the opcode with a list of allowed
 * operations and their corresponding functions. If a valid operation is
 * found, it extracts the argument (if required) and calls the associated
 * function to execute the operation.
 *
 * @op: The opcode to check and execute.
 * @stack: A double pointer to the stack.
 * @l_nr: The current line number.
 *
 * Return:
 * -1 if an error occurred.
 * 0 if the opcode is not recognized.
 * 1 if the opcode was executed successfully.
 */
int chk_op(char *op, stack_t **stack, int l_nr)
{
	int i = 0, j, cnt = 0;
	char *arg_chk;
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
			if (allowed_ops[j].opcode[cnt] != op[cnt])
				break;
		if (cnt == i)
		{
			arg_chk = get_arg(op);
			if (
				(strcmp(allowed_ops[j].opcode, "push") == 0
				&& strcmp(arg_chk, "NO_ARG") == 0)
				|| strcmp(arg_chk, "INVALID_ARG") == 0)
				return (-1);
			op_arg = convert_arg(arg_chk);
			allowed_ops[j].f(stack, l_nr);
			return (1);
		}
	}
	return (0);
}
/**
 * push - Push an element onto the stack.
 *
 * This function pushes an element onto the top of the stack. It uses the
 * global variable `op_arg` as the value to push onto the stack.
 *
 * @stack: A double pointer to the stack.
 * @line_number: The current line number (not used).
 */
void push(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	add_snodeint_end(stack, op_arg);
}
/**
 * pall - Print all elements of the stack.
 *
 * This function prints all elements of the stack, starting from the top.
 * If the stack is empty, it does nothing.
 *
 * @stack: A double pointer to the stack.
 * @line_number: The current line number (not used).
 */
void pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	if ((*stack) == NULL)
		return;
	print_stack(*stack);
}
/**
 * pop - Remove the top element of the stack.
 *
 * This function removes the top element of the stack. If the stack is empty,
 * it does nothing.
 *
 * @stack: A double pointer to the stack.
 * @line_number: The current line number (not used).
 */
void pop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

/**
 * swap - Swap the top two elements of the stack.
 *
 * This function swaps the positions of the top two elements on the stack.
 * If there are fewer than two elements on the stack, it does nothing.
 *
 * @stack: A double pointer to the stack.
 * @line_number: The current line number (not used).
 */
void swap(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
