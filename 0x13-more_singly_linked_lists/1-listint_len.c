#include "lists.h"

/**
 * listint_len_recursive - returns the number of elements in a linked list recursively
 * @h: linked list of type listint_t to traverse
 *
 * Return: number of nodes
 */
size_t listint_len_recursive(const listint_t *h)
{
	if (h == NULL) // Cas de base : si le nœud est NULL, la liste est vide, on retourne 0.
		return 0;

	return 1 + listint_len_recursive(h->next); // Rappel récursif avec le nœud suivant et ajout de 1 au résultat.
}

