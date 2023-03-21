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

static void print_long_formatted_entries(const t_list *const entries_list, const bool print_total_number_of_512_byte_blocks, const bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }

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

static void print_entries_in_columns(t_list *entries_list, size_t column_spacing, ushort terminal_width, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }

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

static void print_entries_per_line(t_list *entries_list, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        mx_printstr(entry->dirent ? entry->dirent->d_name : entry->relative_path);
        mx_printchar('\n');
    }
    if (print_newline_in_the_end) {
        mx_printchar('\n');
    }
}

static void print_dir_name_if(bool print, t_entry *dir) {
    if (print) {
        mx_printstr(dir->relative_path);
        mx_printstr(":\n");
    }
}

static void print_long_formatted_entries_recursively(t_list *directories_list) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;

        print_dir_name_if(true, directory);
        print_long_formatted_entries(directory->entries_list, true, true);

        t_files_dirs files_dirs = mx_separate_entries(directory->entries_list);
        print_long_formatted_entries_recursively(files_dirs.dirs_list);
    }
}

static void print_files_and_directories_in_columns(t_list *entries_list, ushort terminal_width, bool colorized) {
    size_t column_spacing = colorized ? 1 : 8;

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

static void print_files_and_directories_per_line(t_list *entries_list) {
    t_files_dirs files_dirs = mx_separate_entries(entries_list);
    print_entries_per_line(files_dirs.files_list, files_dirs.dirs_list != NULL);

    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;

        if (files_dirs.total_entries_count > 1) {
            mx_printstr(directory->relative_path);
            mx_printstr(":\n");
        }

        print_entries_per_line(directory->entries_list, i->next != NULL);
    }
}

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags) {
    if (output_format == LONG_OUTPUT_FORMAT) {
        t_files_dirs files_dirs = mx_separate_entries(entries_list);
        print_long_formatted_entries(files_dirs.files_list, false, files_dirs.dirs_list != NULL);
        if (print_entries_flags & RECURSIVE_OUTPUT) {
            print_long_formatted_entries_recursively(files_dirs.dirs_list);
        } else {
            for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
                t_entry *dir = (t_entry *)i->data;
                print_dir_name_if(files_dirs.total_entries_count > 1, dir);
                print_long_formatted_entries(dir->entries_list, true, i->next != NULL);
            }
        }
    } else {
        ushort terminal_width = get_terminal_width();

        if (output_format == MULTI_COLUMN_OUTPUT_FORMAT) {
            print_files_and_directories_in_columns(entries_list, terminal_width, print_entries_flags & COLORIZED_OUTPUT);
        } else if (output_format == ONE_ENTRY_PER_LINE_OUTPUT_FORMAT) {
            print_files_and_directories_per_line(entries_list);
        }
    }
}

