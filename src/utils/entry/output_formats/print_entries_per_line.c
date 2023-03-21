#include "../../../../inc/utils.h"

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

void mx_print_files_and_directories_per_line(t_list *entries_list) {
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



