#include "../../../../inc/utils.h"

static size_t *create_empty_size_t_array(size_t size) {
    size_t *array = malloc(size * sizeof(size_t));
    for (size_t i = 0; i < size; i++) {
        array[i] = 0;
    }
    return array;
}

static blkcnt_t get_total_allocated_blocks(t_list *entries_list) {
    blkcnt_t total_allocated_blocks = 0;
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        total_allocated_blocks += ((t_entry *)i->data)->stat.st_blocks;
    }
#ifdef __linux__1
    total_allocated_blocks /= 2;
#endif /* __linux__ */
    return total_allocated_blocks;
}

static size_t *calculate_long_format_column_sizes(t_list *entries) {
    size_t *column_sizes = create_empty_size_t_array(4);
    for (t_list *i = entries; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;

        size_t number_of_links_len = mx_get_digits_count(entry.stat.st_nlink);
        if (number_of_links_len > column_sizes[0]) {
            column_sizes[0] = number_of_links_len;
        }

        size_t owner_name_len = mx_strlen(getpwuid(entry.stat.st_uid)->pw_name);
        if (owner_name_len > column_sizes[1]) {
            column_sizes[1] = owner_name_len;
        }

        size_t group_name_len = mx_strlen(getgrgid(entry.stat.st_gid)->gr_name);
        if (group_name_len > column_sizes[2]) {
            column_sizes[2] = group_name_len;
        }

        size_t number_of_bytes_len = mx_get_digits_count(entry.stat.st_size);
        if (number_of_bytes_len > column_sizes[3]) {
            column_sizes[3] = number_of_bytes_len;
        }
    }
    return column_sizes;
}

static void print_long_formatted_entries(t_list *entries_list, bool print_total_number_of_512_byte_blocks, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }

    if (print_total_number_of_512_byte_blocks) {
        mx_printstr("total ");
        mx_printint(get_total_allocated_blocks((t_list *)entries_list));
        mx_printchar('\n');
    }

    size_t *column_sizes = calculate_long_format_column_sizes((t_list *)entries_list);
    for (const t_list *j = entries_list; j != NULL; j = j->next) {
        t_entry entry = *(t_entry *)j->data;
        mx_print_long_formatted_entry(entry, column_sizes);
    }
    free(column_sizes);

    if (print_newline_in_the_end) {
        mx_printchar('\n');
    }
}

static void print_long_formatted_entries_in_directory_recursively(t_entry *directory, bool print_dir_name, bool print_newline_in_the_beginning) {
    mx_printchar_if(print_newline_in_the_beginning, '\n');
    mx_print_two_strings_if(print_dir_name, directory->relative_path, ":\n");
    print_long_formatted_entries(directory->entries_list, true, false);

    t_files_dirs files_dirs = mx_separate_entries(directory->entries_list);
    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        print_long_formatted_entries_in_directory_recursively((t_entry *)i->data, true, true);
    }
}

static void print_long_formatted_entries_recursively(t_list *directories_list, c_bool print_dir_name) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;
        print_long_formatted_entries_in_directory_recursively(directory, print_dir_name, false);
        mx_printchar_if(i->next != NULL, '\n');
    }
}

void mx_print_long_formatted_files_and_directories(t_list *entries_list, bool recursive) {
    t_files_dirs files_dirs = mx_separate_entries(entries_list);
    print_long_formatted_entries(files_dirs.files_list, false, files_dirs.dirs_list != NULL);
    if (recursive) {
        print_long_formatted_entries_recursively(files_dirs.dirs_list, files_dirs.total_entries_count > 1);
    } else {
        for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
            t_entry *dir = (t_entry *)i->data;
            mx_print_two_strings_if(files_dirs.total_entries_count > 1, dir->relative_path, ":\n");
            print_long_formatted_entries(dir->entries_list, true, i->next != NULL);
        }
    }
}

