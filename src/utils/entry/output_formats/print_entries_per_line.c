#include "../../../../inc/utils.h"

void mx_print_entries_per_line(t_list *entries_list, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        mx_print_two_strings(entry->dirent ? entry->dirent->d_name : entry->relative_path, "\n");
    }
    mx_printchar_if(print_newline_in_the_end, '\n');
}
