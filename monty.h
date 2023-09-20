#ifndef MONTY_H_
#define MONTY_H_

#include <stddef.h>
#include <stdio.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef struct op_s
{
	char *opcode;
	int arg;
} op_t;


int read_file(const char *filepath);
void add_c(char **, char);
void handle_op(char *op, unsigned int l_nr, stack_t **stack);
int chk_op(char *op, stack_t **stack, int l_nr);
void add(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
int get_args(char *arg);
void error_handler(
	int ERRNO,
	stack_t *stack,
	FILE *f_stream,
	const char *file_name,
	unsigned int *line_no,
	char *op_code);

/* stack */
size_t print_stack(const stack_t *h);
size_t stack_len(const stack_t *h);
stack_t *add_snodeint(stack_t **head, const int n);
stack_t *add_snodeint_end(stack_t **head, const int n);
void free_stack(stack_t *head);
stack_t *get_snodeint_at_index(stack_t *head, unsigned int index);
int sum_stack(stack_t *head);
stack_t *insert_snodeint_at_index(stack_t **h, unsigned int idx, int n);
int delete_snodeint_at_index(stack_t **head, unsigned int index);
#endif /*MONTY_H_*/
