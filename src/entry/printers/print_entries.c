#include "../../../inc/entry.h"

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

static ushort get_terminal_width() {
    struct winsize winsize;
    ioctl(0, TIOCGWINSZ, &winsize);
    return winsize.ws_col;
}

static float round_down(float number) {
    float converted_number = (float)((long long)number);
    if (converted_number == number || number >= 0) {
        return converted_number;
    }
    return converted_number - 1;
}

static float round_up(float number) {
    float converted_number = (float)((long long)number);
    if (converted_number == number || number < 0) {
        return converted_number;
    }
    return converted_number + 1;
}

static void print_entries_in_columns(t_list *entries_list, char *column_delimiter, ushort terminal_width) {
    int number_of_entries = mx_list_size(entries_list);
    ushort column_width = get_column_width(entries_list) + mx_strlen(column_delimiter);

    ushort number_of_rows = round_up(number_of_entries / round_down((float)terminal_width / column_width));
    float average_number_of_entries_per_row = (float)number_of_entries / number_of_rows;
    bool average_number_of_entries_per_row_is_integer = average_number_of_entries_per_row == round_up(average_number_of_entries_per_row);
    ushort number_of_columns = average_number_of_entries_per_row_is_integer ? number_of_entries / number_of_rows : terminal_width / column_width;

    for (ushort y = 0; y < number_of_rows; y++) {
        for (ushort x = 0; x < number_of_columns; x++) {
            ushort converted_index = x * number_of_rows + y;
            if (converted_index < number_of_entries) {
                t_entry *entry = (t_entry *)mx_get_by_index(entries_list, converted_index)->data;
                char *printing_str = entry->dirent ? entry->dirent->d_name : entry->relative_path;
                mx_printstr(printing_str);
                mx_printnchar(' ', column_width - mx_strlen(printing_str));
            }
        }
        mx_printchar('\n');
    }
}

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags) {
    int entries_list_size = mx_list_size(entries_list);
    t_list *files_list = NULL;
    t_list *directories_list = NULL;

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        mx_push_back(S_ISDIR(entry.stat.st_mode) ? &directories_list : &files_list, i->data);
    }

    if (output_format == LONG_OUTPUT_FORMAT) {
        if (files_list != NULL) {
            size_t *column_sizes = mx_calculate_long_format_column_sizes(files_list);
            for (t_list *i = files_list; i != NULL; i = i->next) {
                t_entry file = *(t_entry *)i->data;
                mx_print_long_formatted_entry(file, column_sizes);
            }
            free(column_sizes);
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

            size_t *column_sizes = mx_calculate_long_format_column_sizes(directory.entries_list);
            long int total_allocated_blocks = mx_get_total_allocated_blocks(directory.entries_list);
            mx_printstr("total ");
            mx_printint(total_allocated_blocks);
            mx_printchar('\n');
            for (t_list *j = directory.entries_list; j != NULL; j = j->next) {
                t_entry entry = *(t_entry *)j->data;
                mx_print_long_formatted_entry(entry, column_sizes);
            }
            free(column_sizes);

            if (i->next != NULL) {
                mx_printchar('\n');
            }
        }
    } else {
        ushort terminal_width = get_terminal_width();

        if (output_format == MULTI_COLUMN_OUTPUT_FORMAT) {
            char *column_delimiter = print_entries_flags & COLORIZED_OUTPUT ? " " : "        ";
            if (files_list != NULL) {
                print_entries_in_columns(files_list, column_delimiter, terminal_width);
                if (directories_list != NULL) {
                    mx_printchar('\n');
                }
            }

            for (t_list *i = directories_list; i != NULL; i = i->next) {
                t_entry *directory = (t_entry *)i->data;

                if (entries_list_size > 1) {
                    mx_printstr(directory->relative_path);
                    mx_printstr(":\n");
                }

                print_entries_in_columns(directory->entries_list, column_delimiter, terminal_width);

                if (i->next != NULL) {
                    mx_printchar('\n');
                }
            }
        }
    }

    mx_clear_list(&files_list);
    mx_clear_list(&directories_list);
}

