#include "hash_tables.h"

shash_table_t *shash_table_create(unsigned long int size);
int shash_table_set(shash_table_t *ht, const char *key, const char *value);
char *shash_table_get(const shash_table_t *hsht, const char *key);
void shash_table_print(const shash_table_t *hsht);
void shash_table_print_rev(const shash_table_t *hsht);
void shash_table_delete(shash_table_t *hsht);

/**
 * shash_table_create - Creates a sorted hash table.
 * @size: The size of new sorted hash table.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new sorted hash table.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *hsht;
	unsigned long int i;

	hsht = malloc(sizeof(shash_table_t));
	if (hsht == NULL)
		return (NULL);

	hsht->size = size;
	hsht->array = malloc(sizeof(shash_node_t *) * size);
	if (hsht->array == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		hsht->array[i] = NULL;
	hsht->shead = NULL;
	hsht->stail = NULL;

	return (hsht);
}

/**
 * shash_table_set - Adds an element to a sorted hash table.
 * @hsht: A pointer to the sorted hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int shash_table_set(shash_table_t *hsht, const char *key, const char *value)
{
	shash_node_t *new, *tmp;
	char *value_copy;
	unsigned long int index;

	if (hsht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	index = key_index((const unsigned char *)key, hsht->size);
	tmp = hsht->shead;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value_copy;
			return (1);
		}
		tmp = tmp->snext;
	}

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
	{
		free(value_copy);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(value_copy);
		free(new);
		return (0);
	}
	new->value = value_copy;
	new->next = hsht->array[index];
	hsht->array[index] = new;

	if (hsht->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		hsht->shead = new;
		hsht->stail = new;
	}
	else if (strcmp(hsht->shead->key, key) > 0)
	{
		new->sprev = NULL;
		new->snext = hsht->shead;
		hsht->shead->sprev = new;
		hsht->shead = new;
	}
	else
	{
		tmp = hsht->shead;
		while (tmp->snext != NULL && strcmp(tmp->snext->key, key) < 0)
			tmp = tmp->snext;
		new->sprev = tmp;
		new->snext = tmp->snext;
		if (tmp->snext == NULL)
			hsht->stail = new;
		else
			tmp->snext->sprev = new;
		tmp->snext = new;
	}

	return (1);
}

/**
 * shash_table_get - Retrieve the value associated with
 *                   a key in a sorted hash table.
 * @hsht: A pointer to the sorted hash table.
 * @key: The key to get the value of.
 *
 * Return: If the key cannot be matched - NULL.
 *         Otherwise - the value associated with key in hsht.
 */
char *shash_table_get(const shash_table_t *hsht, const char *key)
{
	shash_node_t *node;
	unsigned long int index;

	if (hsht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, hsht->size);
	if (index >= hsht->size)
		return (NULL);

	node = hsht->shead;
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->snext;

	return ((node == NULL) ? NULL : node->value);
}

/**
 * shash_table_print - Prints a sorted hash table in order.
 * @hsht: A pointer to the sorted hash table.
 */
void shash_table_print(const shash_table_t *hsht)
{
	shash_node_t *node;

	if (hsht == NULL)
		return;

	node = hht->shead;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints a sorted hash table in reverse order.
 * @hsht: A pointer to the sorted hash table to print.
 */
void shash_table_print_rev(const shash_table_t *hsht)
{
	shash_node_t *node;

	if (hsht == NULL)
		return;

	node = hsht->stail;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @hsht: A pointer to the sorted hash table.
 */
void shash_table_delete(shash_table_t *hsht)
{
	shash_table_t *head = hsht;
	shash_node_t *node, *tmp;

	if (hsht == NULL)
		return;

	node = hsht->shead;
	while (node)
	{
		tmp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}

	free(head->array);
	free(head);
}
