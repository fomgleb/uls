#include "../../inc/uls.h"

static t_find_entries_flags flags_to_find_entries_flags(t_flags *flags) {
    t_find_entries_flags find_entries_flags = 0;
    find_entries_flags |= (flags->a || flags->A || flags->f ? INCLUDE_ENTRIES_STARTING_WITH_DOT : 0) |
                          (!flags->a && flags->A && !flags->f ? IGNORE_CURRENT_AND_FATHER_DIRECTORY : 0);
    return find_entries_flags;
}

t_list *mx_find_entries_list(t_list *all_inputted_paths_to_entries_list, t_list *invalid_inputted_paths_to_entries_list, t_flags *flags) {
    t_list *entries_list = NULL;

    for (t_list *i = all_inputted_paths_to_entries_list; i != NULL; i = i->next) {
        bool invalid_path_to_entry = false;
        for (t_list *j = invalid_inputted_paths_to_entries_list; j != NULL; j = j->next) {
            if (mx_strcmp(i->data, j->data) == 0) {
                invalid_path_to_entry = true;
            }
        }
        if (invalid_path_to_entry) continue;
        mx_push_front(&entries_list, mx_create_entry_ptr(i->data));
    }

    if (flags->d) {
        return entries_list;
    }

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        if (!S_ISDIR(entry->stat.st_mode)) continue;
        if (flags->R) {
            entry->entries_list = mx_get_entries_in_directory_recursively(*entry, flags_to_find_entries_flags(flags));
        } else {
            entry->entries_list = mx_get_entries_in_directory(*entry, flags_to_find_entries_flags(flags));
        }
    }

    return entries_list;
}
