#include "hash_tables.h"

/**
 * hash_table_delete - Deletes a hash table.
 * @hsht: A pointer to a hash table.
 */
void hash_table_delete(hash_table_t *hsht)
{
	hash_table_t *head = hsht;
	hash_node_t *node, *tmp;
	unsigned long int i;

	for (i = 0; i < hsht->size; i++)
	{
		if (hsht->array[i] != NULL)
		{
			node = hsht->array[i];
			while (node != NULL)
			{
				tmp = node->next;
				free(node->key);
				free(node->value);
				free(node);
				node = tmp;
			}
		}
	}
	free(head->array);
	free(head);
}
