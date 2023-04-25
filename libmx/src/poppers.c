#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
	if (head == NULL || *head == NULL) {
		return;
	}
	t_list *penultimate_node = NULL;
	t_list *last_node = *head;
	for ( ; last_node->next != NULL; last_node = last_node->next)
		penultimate_node = last_node;
	if (last_node == *head)
		*head = NULL;
	free(last_node);
	if (penultimate_node != NULL)
		penultimate_node->next = NULL;
}

void mx_pop_front(t_list **head) {
	if (head == NULL || *head == NULL) {
		return;
	}
	t_list *second_node = (*head)->next;
	free(*head);
	*head = NULL;
	if (second_node != NULL) {
		*head = second_node;
	}
}

void mx_pop_index(t_list **list, int index) {
	if (index < 0)
		index = 0;
	if (index == 0) {
		mx_pop_front(list);
		return;
	}
	t_list *prev_node = *list;
	for (int i = 1; i < index && prev_node->next != NULL; ++i) {
		prev_node = prev_node->next;
	}
	if (prev_node->next == NULL) {
		mx_pop_back(list);
		return;
	}
	t_list *next_node = prev_node->next->next;
	free(prev_node->next);
	prev_node->next = next_node;
}

void mx_pop_node(t_list **head, t_list *node) {
    if (head == NULL || *head == NULL || node == NULL) {
        return;
    }
    if (*head == node) {
        mx_pop_front(head);
        return;
    }
    t_list *prev_node = NULL;
    for (t_list *curr_node = *head; curr_node != NULL; curr_node = curr_node->next) {
        if (curr_node == node) {
            t_list *next_node = curr_node->next;
            free(curr_node);
            prev_node->next = next_node;
            return;
        }
        prev_node = curr_node;
    }
}
