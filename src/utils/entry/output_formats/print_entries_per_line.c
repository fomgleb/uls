#include "../../../../inc/utils.h"

void mx_print_entries_per_line(t_list *entries_list, bool colorized, bool print_newline_in_the_end, bool slash_after_dirs) {
    if (entries_list == NULL) {
        return;
    }
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        mx_print_entry_name(entry, colorized, slash_after_dirs);
        mx_printchar('\n');
    }
    mx_printchar_if(print_newline_in_the_end, '\n');
}
