#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
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
	{"push", push}, {"pall", pall}, {"nop", nop}, {"pint", pint},
	{"pop", pop}, {"swap", swap}, {"add", add}, {"sub", sub},
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
	stack_t *temp;

	(void) line_number;
	temp = malloc(sizeof(stack_t));
	if (temp == NULL)
	{
		error_handler(4, NULL, NULL, NULL, NULL, NULL);
		return;
	}
	temp->next = *stack;
	temp->n = op_arg;
	temp->prev = NULL;

	if (*stack != NULL)
		(*stack)->prev = temp;

	*stack = temp;
}
/**
 * pall - Print all elements of the stack.
 * This function prints all elements of the stack, starting from the top.
 * If the stack is empty, it does nothing.
 *
 * @stack: A double pointer to the stack.
 * @line_number: The current line number (not used).
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *h = (*stack);

	(void) line_number;

	if (stack_len(*stack) == 0)
		return;

	while (h != NULL)
	{
		printf("%i\n", h->n);
		h = h->next;
	}
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
	int len_stack = 0;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack == 0)
	{
		error_handler(6, *stack, NULL, NULL, &line_number, "pop");
		return;
	}

	temp = (*stack);
	*stack = temp->next;
	temp->next = NULL;
	if (temp) /*This check is just to remove the unused variable error*/
	{}
	free(temp);
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
	int len_stack = 0;
	stack_t *temp, *nextP;

	len_stack = stack_len(*stack);

	if (len_stack < 2)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "swap");
		return;
	}

	temp = (*stack);
	nextP = temp->next;

	temp->next = nextP->next;
	temp->prev = nextP;
	nextP->next = temp;
	nextP->prev = NULL;

	if (temp->next != NULL)
		temp->next->prev = temp;

	(*stack) = nextP;
}
