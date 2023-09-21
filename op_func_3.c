#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * mul - Multiplies the top two elements of the stack.
 *
 * This function multiplies the top element of the stack by the second element
 * and stores the result in the top element.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0, result;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack < 2 || *stack == NULL)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "mul");
		return;
	}
	result = (*stack)->n * (*stack)->next->n;

	temp = *stack;
	*stack = temp->next;
	(*stack)->prev = NULL;
	(*stack)->n = result;

	free(temp);
}
/**
 * mod - Computes the modulo of the second
 * element from the top by the top element.
 *
 * This function computes the modulo of the second element from the top of the
 * stack by the top element and stores the result in the top element.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0, result;
	stack_t *temp;

	len_stack = stack_len(*stack);

	if (len_stack < 2 || *stack == NULL)
	{
		error_handler(7, *stack, NULL, NULL, &line_number, "mod");
		return;
	}
	if ((*stack)->n == 0)
	{
		error_handler(9, NULL, NULL, NULL, &line_number, "mod");
		return;
	}
	result = (*stack)->n / (*stack)->next->n;

	temp = *stack;
	*stack = temp->next;
	(*stack)->prev = NULL;
	(*stack)->n = result;

	free(temp);
}
/**
 * pchar - Prints the character at the top of the stack.
 *
 * This function prints the character value at the top of the stack.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0;

	len_stack = stack_len(*stack);

	if (len_stack == 0 || *stack == NULL)
	{
		error_handler(6, *stack, NULL, NULL, &line_number, "pchar");
		return;
	}
	if (!((*stack)->n > 64 && (*stack)->n < 128))
	{
		error_handler(8, NULL, NULL, NULL, &line_number, "pchar");
		return;
	}

	printf("%c\n", (*stack)->n);

}
/**
 * pstr - Prints a string of characters from the stack.
 *
 * This function prints a string of chars from the top of the stack
 * until a non-printable character (outside the ASCII range [65, 127]) or a
 * null byte (0) is encountered.
 *
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number of the bytecode instruction.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	int len_stack = 0;
	stack_t *tmp;

	(void) line_number;
	len_stack = stack_len(*stack);

	tmp = (*stack);
	while (*stack != NULL && len_stack != 0 && tmp->next != NULL)
	{
		if (!(tmp->n > 64 && tmp->n < 128) || tmp->n == 0)
			break;
		printf("%c", tmp->n);

		tmp = tmp->next;
	}
	printf("\n");
}
