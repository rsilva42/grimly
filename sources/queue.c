#include "grimly.h"

t_queue *new_queue_node(t_mapnode *node, t_queue *prev, t_queue *next) {
	t_queue *new = malloc(sizeof(t_queue));

	new->node = node;
	new->prev = prev;
	new->next = next;

	return new;
}

t_mapnode *dequeue(t_queue **head) {
	t_queue *to_pop = NULL;

	if (head && *head) {
		to_pop = *head;
		*head = to_pop->next;

		if (*head)
			(*head)->prev = NULL;
		to_pop->next = NULL;

	}

	if (to_pop)
		return to_pop->node;
	else
		return NULL;
}

void enqueue(t_queue **head, t_mapnode *to_push) {
	t_queue *node;

	if (head && *head) {
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_queue_node(to_push, node, NULL);
	} else if (*head == NULL) {
		*head = new_queue_node(to_push, NULL, NULL);
	}
}
