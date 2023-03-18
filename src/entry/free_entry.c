#include "../../inc/entry.h"

void mx_free_entry(t_entry entry) {
    free(entry.relative_path);
    free(entry.dirent);
    for (t_list *node = entry.entries_list; node != NULL; node = node->next) {
        mx_free_entry(*(t_entry *)node->data);
        free(node->data);
    }
    mx_clear_list(&entry.entries_list);
}

void mx_free_entry_ptr(t_entry **entry) {
    mx_free_entry(**entry);
    free(*entry);
    *entry = NULL;
}

