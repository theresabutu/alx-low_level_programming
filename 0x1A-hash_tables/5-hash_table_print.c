#include "hash_tables.h"

/**
 * hash_table_print - Prints a hash table.
 * @hsht: A pointer to the hash table to print.
 *
 * Description: Key/value pairs are printed in the order
 *              they appear in the array of the hash table.
 */
void hash_table_print(const hash_table_t *hsht)
{
	hash_node_t *node;
	unsigned long int i;
	unsigned char comma_flag = 0;

	if (hsht == NULL)
		return;

	printf("{");
	for (i = 0; i < hsht->size; i++)
	{
		if (hsht->array[i] != NULL)
		{
			if (comma_flag == 1)
				printf(", ");

			node = hsht->array[i];
			while (node != NULL)
			{
				printf("'%s': '%s'", node->key, node->value);
				node = node->next;
				if (node != NULL)
					printf(", ");
			}
			comma_flag = 1;
		}
	}
	printf("}\n");
}
