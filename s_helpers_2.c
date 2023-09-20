#include "monty.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * delete_snodeint_at_index - Delete a node at a given index.
 *
 * This function deletes the node at the specified index 'index' in a doubly
 * linked stack. If the index is out of range, it returns -1. If the deletion
 * is successful, it returns 1.
 *
 * @head: Pointer to a pointer to the head of the stack.
 * @index: The index of the node to delete.
 *
 * Return: 1 if deletion is successful, -1 if index is out of range.
 */
int delete_snodeint_at_index(stack_t **head, unsigned int index)
{
	unsigned int i = 0;
	stack_t *temp, *del_node;

	if (head == NULL || *head == NULL)
		return (-1);

	temp = *head;
	while (temp != NULL)
	{
		if (i == index)
		{
			del_node = temp;

			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			if (temp->prev != NULL && temp->next != NULL)
				temp->prev->next = temp->next;
			else
				*head = temp->next;
			del_node->prev = NULL;
			del_node->next = NULL;
			return (1);
		}
		i++;
		temp = temp->next;
	}
	return (-1);
}

/**
 * add_snodeint_end - Add node to end.
 *
 * @head: Pointer to stack's head.
 * @n: Integer value for new node.
 *
 * Return: Pointer to new node or NULL.
 */
stack_t *add_snodeint_end(stack_t **head, const int n)
{
	stack_t *temp, *cpy;

	temp = malloc(sizeof(stack_t));
	if (temp == NULL)
		return (NULL);

	temp->next = NULL;
	temp->n = n;
	temp->prev = NULL;

	if (*head == NULL)
	{
		*head = temp;
		return (*head);
	}

	cpy = *head;
	while (cpy->next != NULL)
	{
		cpy = cpy->next;
	}
	cpy->next = temp;
	temp->prev = cpy;

	return (*head);
}

/**
 * print_stack - Print stack.
 *
 * Print the elements of a stack and count nodes.
 *
 * @h: Pointer to stack's head.
 *
 * Return: Number of nodes in stack.
 */
size_t print_stack(const stack_t *h)
{
	int i = 0;

	while (h->next != NULL)
	{
		h = h->next;
		i++;
	}
	while (h != NULL)
	{
		printf("%d\n", h->n);
		h = h->prev;
	}

	return (i + 1);
}

/**
 * free_stack - Free a stack.
 *
 * This function frees the memory allocated for a stack
 * and all its nodes, starting from the end of the stack and moving
 * towards the beginning.
 *
 * @head: Pointer to the head of the stack.
 */
void free_stack(stack_t *head)
{
	stack_t *temp;

	if (head == NULL)
		return;

	while (head->next != NULL)
		head = head->next;

	while (head != NULL)
	{
		temp = head;
		head = head->prev;

		free(temp);
	}
}
