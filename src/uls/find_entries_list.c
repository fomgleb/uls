#include "../../inc/uls.h"

t_list *mx_find_entries_list(t_list *input_entry_names_list, t_flags *flags) {
    t_list *entries_list = NULL;

    for (t_list *node = input_entry_names_list; node != NULL; node = node->next) {
        mx_push_front(&entries_list, mx_create_entry_ptr(node->data));
    }

    if (flags->d) {
        return entries_list;
    } else if (flags->R) {
        for (t_list *i = entries_list; i != NULL; i = i->next) {
            t_entry *entry = (t_entry *)i->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory_recursively(*entry, flags->a || flags->A || flags->f, !flags->a && flags->A && !flags->f);
            }
        }
    } else {
        for (t_list *node = entries_list; node != NULL; node = node->next) {
            t_entry *entry = (t_entry *)node->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory(*entry, flags->a || flags->A || flags->f, !flags->a && flags->A && !flags->f);
            }
        }
    }

    return entries_list;
}
