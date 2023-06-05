#include "lists.h"

/**
 * print_listint - prints all the elements of a linked list
 * @h: linked list of type listint_t to print
 *
 * Return: number of nodes
 */
size_t print_listint(const listint_t *y)
{
	size_t num = 0;

	while (y)
	{
		printf("%d\n", y->n);
		num++;
		y = y->next;
	}

	return (num);
}
