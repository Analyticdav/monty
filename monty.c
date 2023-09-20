#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

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
