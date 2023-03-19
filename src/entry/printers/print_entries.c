#include "../../../inc/entry.h"

void mx_print_entries(t_list *entries_list, t_flags flags) {
    int entries_list_size = mx_list_size(entries_list);
    t_list *files_list = NULL;
    t_list *directories_list = NULL;

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        mx_push_back(S_ISDIR(entry.stat.st_mode) ? &directories_list : &files_list, i->data);
    }

    if (flags.l) {
        if (files_list != NULL) {
            t_long_format_column_sizes column_sizes = mx_calculate_long_format_column_sizes(files_list);
            for (t_list *i = files_list; i != NULL; i = i->next) {
                t_entry file = *(t_entry *)i->data;
                mx_print_long_formatted_entry(file, column_sizes);
            }
            if (directories_list != NULL) {
                mx_printchar('\n');
            }
        }

        for (t_list *i = directories_list; i != NULL; i = i->next) {
            t_entry directory = *(t_entry *)i->data;

            if (entries_list_size > 1) {
                mx_printstr(directory.relative_path);
                mx_printstr(":\n");
            }

            t_long_format_column_sizes long_format_column_sizes = mx_calculate_long_format_column_sizes(directory.entries_list);
            long int total_allocated_blocks = mx_get_total_allocated_blocks(directory.entries_list);
            mx_printstr("total ");
            mx_printint(total_allocated_blocks);
            mx_printchar('\n');
            for (t_list *j = directory.entries_list; j != NULL; j = j->next) {
                t_entry entry = *(t_entry *)j->data;
                mx_print_long_formatted_entry(entry, long_format_column_sizes);
            }

            if (i->next != NULL) {
                mx_printchar('\n');
            }
        }
    }

    mx_clear_list(&files_list);
    mx_clear_list(&directories_list);
}

