#include "monty.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * stack_len - Get the number of elements in a stack.
 *
 * This function returns the number of elements (nodes) in a given
 * stack.
 *
 * @h: Pointer to the head of the stack.
 *
 * Return: The number of elements in the stack.
 */
size_t stack_len(const stack_t *h)
{
	int i = 0;

	while (h != NULL)
	{
		i++;
		h = h->next;
	}
	return (i);
}

/**
 * add_snodeint - Add a new node at the beginning of a stack.
 * @head: A pointer to a pointer to the head of the stack.
 * @n: The integer value to store in the new node.
 *
 * Return: A pointer to the newly added node, or NULL if
 * memory allocation fails.
 */
stack_t *add_snodeint(stack_t **head, const int n)
{
	stack_t *temp;

	temp = malloc(sizeof(stack_t));
	if (temp == NULL)
		return (NULL);
	temp->next = *head;
	temp->n = n;
	temp->prev = NULL;

	if (*head != NULL)
		(*head)->prev = temp;

	*head = temp;

	return (temp);
}

/**
 * get_snodeint_at_index - Get node at specified index.
 *
 * @head: Pointer to the head of the stack.
 * @index: The index of the node to retrieve.
 *
 * Return: Pointer to the node at the index,
 * or NULL if not found.
 */
stack_t *get_snodeint_at_index(stack_t *head, unsigned int index)
{
	unsigned int i = 0;

	while (head != NULL)
	{
		if (i == index)
		{
			return (head);
		}
		head = head->next;
		i++;
	}
	return (NULL);
}

/**
 * sum_stack - Calculate the sum of stack elements.
 * @head: Pointer to the head of the stack.
 *
 * Return: The sum of stack elements or 0 if the list is empty.
 */
int sum_stack(stack_t *head)
{
	int sum = 0;

	if (head == NULL)
		return (sum);

	while (head != NULL)
	{
		sum += head->n;
		head = head->next;
	}
	return (sum);
}

/**
 * insert_snodeint_at_index - Insert a new node at a given index.
 *
 * This function inserts a new node with the specified value 'n' at the
 * given index 'idx' in a stack. If the index is out of range
 * or memory allocation fails, it returns NULL.
 *
 * @h: Pointer to a pointer to the head of the stack.
 * @idx: The index at which to insert the new node.
 * @n: The integer value to store in the new node.
 *
 * Return: Pointer to the new node or NULL if not inserted.
 */
stack_t *insert_snodeint_at_index(stack_t **h, unsigned int idx, int n)
{
	stack_t *node, *temp, *p_node;
	unsigned int i = 0;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		return (NULL);

	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	temp = *h;
	while (temp != NULL)
	{
		if (i == idx)
		{
			if (temp->prev == NULL)
			{
				free(node);
				return (add_snodeint(h, n));
			}
			p_node = temp->next;

			node->prev = temp->prev;
			node->next = temp;

			temp->prev->next = node;
			temp->prev = node;
			temp->next = p_node;
			return (node);
		}
		temp = temp->next;
		i++;
	}
	free(node);
	return (NULL);
}

