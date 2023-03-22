#include "../../../../inc/utils.h"

static void print_entries(t_list *entries_list, bool print_newline_in_the_end) {
    if (entries_list == NULL) {
        return;
    }
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        mx_print_two_strings(entry->dirent ? entry->dirent->d_name : entry->relative_path, "\n");
    }
    mx_printchar_if(print_newline_in_the_end, '\n');
}

static void print_contents_of_directories(t_list *directories_list, bool print_names_of_dirs) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;
        mx_print_two_strings_if(print_names_of_dirs, directory->relative_path, ":\n");
        print_entries(directory->entries_list, i->next != NULL);
    }
}

static void print_directory_content_recursively(t_entry *directory, bool print_dir_name, bool print_newline_in_the_beginning) {
    mx_printchar_if(print_newline_in_the_beginning, '\n');
    mx_print_two_strings_if(print_dir_name, directory->relative_path, ":\n");
    print_entries(directory->entries_list, false);

    t_files_dirs files_dirs = mx_separate_entries(directory->entries_list);
    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        print_directory_content_recursively((t_entry *)i->data, true, true);
    }
}

static void print_contents_of_directories_recursively(t_list *directories_list) {
    for (t_list *i = directories_list; i != NULL; i = i->next) {
        t_entry *directory = (t_entry *)i->data;
        print_directory_content_recursively(directory, directories_list->next != NULL, false);
        mx_printchar_if(i->next != NULL, '\n');
    }
}

void mx_print_files_and_directories_per_line(t_list *entries_list, bool recursively) {
    t_files_dirs files_dirs = mx_separate_entries(entries_list);
    print_entries(files_dirs.files_list, files_dirs.dirs_list != NULL);
    if (recursively) {
        print_contents_of_directories_recursively(files_dirs.dirs_list);
    } else {
        print_contents_of_directories(files_dirs.dirs_list, files_dirs.total_entries_count > 1);
    }
}

