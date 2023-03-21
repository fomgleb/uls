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

static void print_entries_in_columns(t_list *entries_list, size_t column_spacing, ushort terminal_width, bool print_newline_in_the_end) {
    int number_of_entries = mx_list_size(entries_list);
    ushort column_width = get_column_width(entries_list) + column_spacing;

    ushort number_of_rows = round_up(number_of_entries / round_down((float)terminal_width / column_width));
    float average_number_of_entries_per_row = (float)number_of_entries / number_of_rows;
    bool average_number_of_entries_per_row_is_integer = average_number_of_entries_per_row == round_up(average_number_of_entries_per_row);
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

static void print_long_formatted_entries(const t_list *const entries_list, const bool print_total_number_of_512_byte_blocks, const bool print_newline_in_the_end) {
    if (print_total_number_of_512_byte_blocks) {
        mx_printstr("total ");
        mx_printint(mx_get_total_allocated_blocks((t_list *)entries_list));
        mx_printchar('\n');
    }

    size_t *column_sizes = mx_calculate_long_format_column_sizes((t_list *)entries_list);
    for (const t_list *j = entries_list; j != NULL; j = j->next) {
        t_entry entry = *(t_entry *)j->data;
        mx_print_long_formatted_entry(entry, column_sizes);
    }
    free(column_sizes);

    if (print_newline_in_the_end) {
        mx_printchar('\n');
    }
}

static void print_long_formatted_files_and_directories(t_list *files_list, t_list *directories_list, size_t all_entries_count) {
    if (files_list != NULL) {
        print_long_formatted_entries(files_list, false, directories_list != NULL);
    }

    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry directory = *(t_entry *)i->data;

        if (all_entries_count > 1) {
            mx_printstr(directory.relative_path);
            mx_printstr(":\n");
        }

        print_long_formatted_entries(directory.entries_list, true, i->next != NULL);
    }
}

static void print_files_and_directories_in_columns(t_list *files_list, t_list *directories_list, size_t all_entries_count, ushort terminal_width, bool colorized) {
    size_t column_spacing = colorized ? 1 : 8;
    if (files_list != NULL) {
        print_entries_in_columns(files_list, column_spacing, terminal_width, directories_list != NULL);
    }

    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;

        if (all_entries_count > 1) {
            mx_printstr(directory->relative_path);
            mx_printstr(":\n");
        }

        print_entries_in_columns(directory->entries_list, column_spacing, terminal_width, i->next != NULL);
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
        print_long_formatted_files_and_directories(files_list, directories_list, entries_list_size);
    } else {
        ushort terminal_width = get_terminal_width();

        if (output_format == MULTI_COLUMN_OUTPUT_FORMAT) {
            print_files_and_directories_in_columns(files_list, directories_list, entries_list_size, terminal_width, print_entries_flags & COLORIZED_OUTPUT);
        }
    }

    mx_clear_list(&files_list);
    mx_clear_list(&directories_list);
}

