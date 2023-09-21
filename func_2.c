#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * handle_op - Handle a Monty opcode.
 *
 * This function checks and handles a Monty opcode. It calls `chk_op` to
 * validate and execute the opcode. If the opcode is invalid or an error
 * occurs during execution, it calls `error_handler` to report the error.
 *
 * @op: The Monty opcode to handle.
 * @l_nr: The current line number.
 * @stack: A double pointer to the stack.
 */
void handle_op(char *op, unsigned int l_nr, stack_t **stack)
{
	int res;

	res = chk_op(op, stack, l_nr);
	if (res < 0)
		error_handler(5, *stack, NULL, NULL, &l_nr, op);
	else if (res == 0)
		error_handler(2, *stack, NULL, NULL, &l_nr, op);
}
/**
 * convert_arg - Convert a string argument to an integer.
 *
 * This function converts a string argument to an integer. It takes into
 * account whether the argument is negative and returns the corresponding
 * integer value. It assumes the input string is a valid integer.
 *
 * @arg: The string argument to convert.
 *
 * Return:
 * The integer value of the argument.
 */
int convert_arg(char *arg)
{
	int arg_i = 0, is_negative = 0;

	if (*arg == '-')
	{
		arg = arg + 1;
		is_negative = 1;
	}

	arg_i = atoi(arg);
	if (is_negative)
		arg_i *= -1;
	return (arg_i);
}
