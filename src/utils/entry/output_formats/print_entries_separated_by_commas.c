#include "../../../../inc/utils.h"

void mx_print_entries_separated_by_commas(t_list *entries_list, ushort terminal_width, c_entry_printing_flags flags) {
    if (entries_list == NULL) return;

    size_t printed_symbols_count_on_line = 0;
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;

        size_t entry_size = mx_strlen(entry->dirent ? entry->dirent->d_name : entry->relative_path);

        if (printed_symbols_count_on_line + entry_size + (i->next ? 2 : 0) >= terminal_width) {
            mx_printchar('\n');
            printed_symbols_count_on_line = 0;
        }

        printed_symbols_count_on_line += mx_print_entry_name(entry, flags & IS_COLORIZED, flags & PRINT_SLASH_AFTER_DIRECTORIES);
        printed_symbols_count_on_line += mx_printstr_if(i->next, ", ");
    }
    mx_printchar('\n');
}
