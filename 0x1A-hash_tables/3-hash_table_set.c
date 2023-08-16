#include "hash_tables.h"

/**
 * hash_table_set - Add or update an element in a hash table.
 * @hsht: A pointer to the hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int hash_table_set(hash_table_t *hsht, const char *key, const char *value)
{
	hash_node_t *new;
	char *value_copy;
	unsigned long int index, i;

	if (hsht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	index = key_index((const unsigned char *)key, hsht->size);
	for (i = index; hsht->array[i]; i++)
	{
		if (strcmp(hsht->array[i]->key, key) == 0)
		{
			free(hsht->array[i]->value);
			hsht->array[i]->value = value_copy;
			return (1);
		}
	}

	new = malloc(sizeof(hash_node_t));
	if (new == NULL)
	{
		free(value_copy);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (0);
	}
	new->value = value_copy;
	new->next = hsht->array[index];
	hsht->array[index] = new;

	return (1);
}
