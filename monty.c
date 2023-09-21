#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point for the Monty interpreter.
 *
 * This function is the entry point for the Monty interpreter. It checks if
 * the correct number of command-line arguments is provided, reads and
 * interprets Monty bytecode from a file, and handles errors using the
 * `error_handler` function.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return:
 *  - 0 on success.
 *  - EXIT_FAILURE if there is an error.
 */
int main(int argc, char *argv[])
{
	(void) argc;
	if (argc != 2)
	{
		error_handler(3, NULL, NULL, NULL, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	read_file(argv[1]);
	return (0);
}
