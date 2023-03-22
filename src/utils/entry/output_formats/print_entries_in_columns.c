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

static void print_entries(t_list *entries_list, c_char column_delimiter, ushort terminal_width, bool print_newline_in_the_end) {
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

static void print_contents_of_directories(t_list *directories_list, c_char column_delimiter, c_ushort terminal_width, c_bool print_names_of_dirs) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;
        mx_print_two_strings_if(print_names_of_dirs, directory->relative_path, ":\n");
        print_entries(directory->entries_list, column_delimiter, terminal_width, i->next != NULL);
    }
}

static void print_directory_content_recursively(t_entry *directory, c_char column_delimiter, c_ushort terminal_width, bool print_dir_name, bool print_newline_in_the_beginning) {
    mx_printchar_if(print_newline_in_the_beginning, '\n');
    mx_print_two_strings_if(print_dir_name, directory->relative_path, ":\n");
    print_entries(directory->entries_list, column_delimiter, terminal_width, false);

    t_files_dirs files_dirs = mx_separate_entries(directory->entries_list);
    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        print_directory_content_recursively((t_entry *)i->data, column_delimiter, terminal_width, true, true);
    }
}

static void print_contents_of_directories_recursively(t_list *directories_list, c_char column_delimiter, c_ushort terminal_width, bool print_dir_name) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;
        print_directory_content_recursively(directory, column_delimiter, terminal_width, print_dir_name, false);
        mx_printchar_if(i->next != NULL, '\n');
    }
}

void mx_print_files_and_directories_in_columns(t_list *entries_list, c_bool colorized, c_bool recursively) {
    c_char column_delimiter = colorized ? ' ' : '\t';
    ushort terminal_width = mx_get_terminal_width();
    t_files_dirs files_dirs = mx_separate_entries(entries_list);
    print_entries(files_dirs.files_list, column_delimiter, terminal_width, files_dirs.dirs_list != NULL);
    if (recursively) {
        print_contents_of_directories_recursively(files_dirs.dirs_list, column_delimiter, terminal_width, files_dirs.total_entries_count > 1);
    } else {
        print_contents_of_directories(files_dirs.dirs_list, column_delimiter, terminal_width, files_dirs.total_entries_count > 1);
    }
}

