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

void mx_print_entries_in_columns(t_list *entries_list, c_char column_delimiter, ushort terminal_width, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }

    int number_of_entries = mx_list_size(entries_list);
    ushort column_width = get_column_width(entries_list);

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
                    mx_printchar(column_delimiter);
                }
            }
        }
        mx_printchar('\n');
    }

    mx_printchar_if(print_newline_in_the_end, '\n');
}
