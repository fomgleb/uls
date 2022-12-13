#include "../inc/main.h"

int main(int argc, char **argv) {
    const char *EXISTING_FLAGS = "ARSUacdflrtu";

    t_args args = mx_convert_to_args(argc, argv);
    mx_prepare_args(&args, EXISTING_FLAGS);
    t_flags flags = mx_create_flags(args.flags_str);
    t_list *entries_list = mx_find_entries_list(args.entry_names_list, flags);
    mx_sort_entries_list_recursively(entries_list, flags);
    mx_print_entries_list(entries_list, flags);
    

    mx_free_main_variables(args, entries_list);

    return 0;

    
}

void mx_prepare_args(t_args *args, const char *existing_args) {
    t_args_error args_error = mx_validate_args(*args, existing_args);

    mx_print_args_error(args_error, existing_args);
    if (args_error.error_code == ILLEGAL_FLAG) {
        mx_free_main_variables(*args, NULL);
        exit(0);
    }
    for (t_list *invalid = args_error.invalid_entry_names_list; invalid != NULL; invalid = invalid->next) {
        for (t_list *exist = args->entry_names_list; exist != NULL;) {
            if (mx_strcmp(invalid->data, exist->data) == 0) {
                t_list *next_node = exist->next;
                free(exist->data);
                mx_pop_node(&args->entry_names_list, exist);
                exist = next_node;
                continue;
            }
            exist = exist->next;
        }
    }

    mx_free_args_error(args_error);
}

t_list *mx_find_entries_list(t_list *input_entry_names_list, t_flags flags) {
    t_list *entries_list = NULL;

    for (t_list *node = input_entry_names_list; node != NULL; node = node->next) {
        mx_push_front(&entries_list, mx_create_entry_ptr(node->data));
    }

    if (flags.d) {
        return entries_list;
    } else if (flags.R) {
        for (t_list *i = entries_list; i != NULL; i = i->next) {
            t_entry *entry = (t_entry *)i->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory_recursively(*entry, flags.a || flags.A, !flags.a && flags.A);
            }
        }
    } else {
        for (t_list *node = entries_list; node != NULL; node = node->next) {
            t_entry *entry = (t_entry *)node->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory(*entry, flags.a || flags.A, !flags.a && flags.A);
            }
        }
    }

    return entries_list;
}

void mx_sort_entries_list_recursively(t_list *entries_list, t_flags flags) {
    if (flags.f) {
        return;
    } else if (flags.S) {
        mx_sort_list(entries_list, mx_sort_entries_by_size);
    } else if (flags.t) {
        if (flags.u > flags.U && flags.u > flags.c) {
            mx_sort_list(entries_list, mx_sort_entries_by_last_access);
        } else if (flags.U > flags.u && flags.U > flags.c) {
            mx_sort_list(entries_list, mx_sort_entries_by_creation_time);
        } else {
            mx_sort_list(entries_list, mx_sort_entries_by_last_modification);
        }
    } else {
        mx_sort_list(entries_list, mx_sort_entries_by_name);
    }

    if (flags.r) {
        mx_reverse_list(entries_list);
    }

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        mx_sort_entries_list_recursively(((t_entry *)i->data)->entries_list, flags);
    }
}

void mx_print_entries_list(t_list *entries_list, t_flags flags) {
    if (flags.l) {
        int sum_of_file_sizes = 0;
        for (t_list *i = entries_list; i != NULL; i = i->next) {
            for (t_list *j = (*(t_entry *)i->data).entries_list; j != NULL; j = j->next) {
                sum_of_file_sizes += (*(t_entry *)j->data).stat.st_blocks;
            }
        }
        mx_printstr("total ");
        mx_printint(sum_of_file_sizes);
        mx_printchar(' ');
        for (t_list *i = (*(t_entry *)entries_list->data).entries_list; i != NULL; i = i->next) {
            t_entry entry = *(t_entry *)i->data;
            mx_printstr(mx_get_permissions_str(entry.stat.st_mode, entry.relative_path));
            mx_printchar(' ');
            mx_printstr(entry.relative_path);
            mx_printchar('\n');
        }
    }

    // for (t_list *i = entries_list; i != NULL; i = i->next) {
    //     t_entry entry = *(t_entry *)i->data;
    //     if (S_ISREG(entry.stat.st_mode)) {
    //         mx_printstr(entry.relative_path);
    //         mx_printchar('\n');    
    //     }
    // }
    // mx_printchar('\n');
    // for (t_list *i = entries_list; i != NULL; i = i->next) {
    //     t_entry entry = *(t_entry *)i->data;
    //     if (S_ISDIR(entry.stat.st_mode)) {
    //         mx_print_directory_content_recursively(entry, flags);
    //     }
    // }

    // int list_size = 100;
    // char *list = malloc(list_size);
    // ssize_t size = listxattr(".", list, list_size);

    // mx_printstr("Some stuff:\n");
    // mx_printstr("Size = ");
    // mx_printint(size);
    // mx_printchar('\n');
    // for (int i = 0; i < size; ) {
    //     mx_printchar(list[i]);
    //     if (list[i] == '\0') {
    //         i++;
    //         mx_printchar('\n');
    //     }
    // }
}

// void mx_print_entry(t_entry entry, t_flags flags) {

// }

// void mx_print

// void mx_print_directory_content_recursively(t_entry directory) {
//     mx_printstr(directory.relative_path);
//     mx_printstr(":\n");
//     for (t_list *i = directory.entries_list; i != NULL; i = i->next) {
//         t_entry entry = *(t_entry *)i->data;
//         mx_printint(entry.stat.st_blksize);
//         mx_printchar(' ');
//         mx_printint(entry.stat.st_blocks);
//         mx_printchar(' ');
//         mx_printstr(entry.dirent->d_name);
//         mx_printchar('\n');
//     }
//     mx_printchar('\n');
//     for (t_list *i = directory.entries_list; i != NULL; i = i->next) {
//         t_entry entry = *(t_entry *)i->data;
//         if (S_ISDIR(entry.stat.st_mode) && mx_strcmp(entry.dirent->d_name, ".") != 0 && mx_strcmp(entry.dirent->d_name, "..") != 0) {
//             mx_print_directory_content_recursively(entry);
//         }
//     }
// }

void mx_free_main_variables(t_args args, t_list *entries_list) {
    for (t_list *node = entries_list; node != NULL; node = node->next) {
        t_entry *entry = (t_entry *)node->data;
        mx_free_entry_ptr(&entry);
    }
    mx_clear_list(&entries_list);
    mx_free_args(args);
}

