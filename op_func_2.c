#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * sub - Subtracts the top two elements of the stack.
 *
 * This function subtracts the second element from
 * the top of the stack from the top element and
 * stores the result in the top element.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0, result;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack < 2)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "sub");
		return;
	}
	result = (*stack)->n - (*stack)->next->n;

	temp = *stack;
	*stack = temp->next;
	(*stack)->prev = NULL;
	(*stack)->n = result;

	free(temp);
}
/**
 * nop - Does nothing :).
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
/**
 * add - Adds the top two elements of the stack.
 *
 * This function adds the top two elements of the stack
 * and stores the result in the top element.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void add(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0, result;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack < 2)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "add");
		return;
	}
	result = (*stack)->n + (*stack)->next->n;

	temp = *stack;
	*stack = temp->next;
	(*stack)->prev = NULL;
	(*stack)->n = result;

	free(temp);
}
/**
 * pint - Prints the top element of the stack.
 *
 * This function prints the top element of the stack without removing it.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0;

	len_stack = stack_len(*stack);

	if (len_stack == 0)
	{
		error_handler(6, *stack, NULL, NULL, &line_number, "pint");
		return;
	}
	printf("%i\n", (*stack)->n);
}
/**
 * mdiv - Divides the second element from the top by the top element.
 *
 * This function divides the second element from the top of the
 * stack by the top element and stores the result in the top element.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void mdiv(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0, result;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack < 2 || *stack == NULL)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "div");
		return;
	}
	if ((*stack)->n == 0)
	{
		error_handler(9, NULL, NULL, NULL, &line_number, NULL);
		return;
	}
	result = (*stack)->n / (*stack)->next->n;

	temp = *stack;
	*stack = temp->next;
	(*stack)->prev = NULL;
	(*stack)->n = result;

	free(temp);
}
