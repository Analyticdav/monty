#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

void push(int value){
stack_t* new_node = (stack_t*)malloc(sizeof(stack_t));
if (new_node == NULL)
{
perror("Memory allocation error");
exit(1);
}
new_node->data = value;
new_node->next = top;
top = new_node;
}

int pop() 
{
if (top == NULL)
{
printf("Stack underflow\n");
exit(1);
}
int value = top->data;
stack_t* temp = top;
top = top->next;
free(temp);
return value;
}

void pint() {
if (top == NULL)
{
printf("L<line_number>: can't pint, stack empty\n");
exit(EXIT_FAILURE);
}
printf("%d\n", top->data);
}
