#include "../../../../inc/utils.h"

static ushort get_column_width(t_list *entries_list) {
    ushort column_width = 0;
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        size_t entry_name_len = mx_strlen(entry->dirent ? entry->dirent->d_name : entry->relative_path);
        if (entry_name_len > column_width) {
            column_width = entry_name_len;
        }
    }
    return column_width;
}

static void print_entries_in_columns(t_list *entries_list, size_t column_spacing, ushort terminal_width, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }

    int number_of_entries = mx_list_size(entries_list);
    ushort column_width = get_column_width(entries_list) + column_spacing;

    ushort number_of_rows = mx_round_up(number_of_entries / mx_round_down((float)terminal_width / column_width));
    float average_number_of_entries_per_row = (float)number_of_entries / number_of_rows;
    bool average_number_of_entries_per_row_is_integer = average_number_of_entries_per_row == mx_round_up(average_number_of_entries_per_row);
    ushort number_of_columns = average_number_of_entries_per_row_is_integer ? number_of_entries / number_of_rows : terminal_width / column_width;

    for (ushort y = 0; y < number_of_rows; y++) {
        for (ushort x = 0; x < number_of_columns; x++) {
            ushort converted_index = x * number_of_rows + y;
            if (converted_index < number_of_entries) {
                t_entry *entry = (t_entry *)mx_get_by_index(entries_list, converted_index)->data;
                char *printing_string = entry->dirent ? entry->dirent->d_name : entry->relative_path;
                size_t printing_string_length = mx_printstr(printing_string);
                if (x + 1 != number_of_columns) {
                    mx_printnchar(' ', column_width - printing_string_length);
                }
            }
        }
        mx_printchar('\n');
    }

    if (print_newline_in_the_end) {
        mx_printchar('\n');
    }
}

void mx_print_files_and_directories_in_columns(t_list *entries_list, bool colorized) {
    size_t column_spacing = colorized ? 1 : 8;
    ushort terminal_width = mx_get_terminal_width();

    t_files_dirs files_dirs = mx_separate_entries(entries_list);
    print_entries_in_columns(files_dirs.files_list, column_spacing, terminal_width, files_dirs.dirs_list != NULL);

    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;

        if (files_dirs.total_entries_count > 1) {
            mx_printstr(directory->relative_path);
            mx_printstr(":\n");
        }

        print_entries_in_columns(directory->entries_list, column_spacing, terminal_width, i->next != NULL);
    }
}

