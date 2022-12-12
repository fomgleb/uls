#include "../inc/main.h"

int main(int argc, char **argv) {
    const char *EXISTING_FLAGS = "ARSadftu";

    t_args args = mx_convert_to_args(argc, argv);
    mx_prepare_args(&args, EXISTING_FLAGS);
    t_list *entries_list = mx_find_entries_list(args);

    mx_sort_entries_list_recursively(entries_list, args);

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        if (S_ISREG(entry.stat.st_mode)) {
            mx_printstr(entry.relative_path);
            mx_printchar('\n');    
        }
    }
    mx_printchar('\n');
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        if (S_ISDIR(entry.stat.st_mode)) {
            mx_print_directory_content_recursively(entry);
        }
    }

    mx_free_main_variables(args, entries_list);

    return 0;

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

t_list *mx_find_entries_list(t_args args) {
    t_list *entries_list = NULL;
    t_selection_flags flags = mx_create_selection_flags(args.flags);

    for (t_list *node = args.entry_names_list; node != NULL; node = node->next) {
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

void mx_sort_entries_list_recursively(t_list *entries_list, t_args args) {
    t_sorting_flags flags = mx_create_sorting_flags(args.flags);

    

    if (flags.f) {
        return;
    } else if (flags.S) {
        mx_sort_list(entries_list, mx_sort_entries_by_size);
    } else if (flags.t) {
        if (flags.u > flags.U && flags.u > flags.c) {
            mx_sort_list(entries_list, mx_sort_entries_by_last_access);
        } else if (flags.U > flags.u && flags.U > flags.c) {

        }
    } else {
        mx_sort_list(entries_list, mx_sort_entries_by_name);
    }

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        mx_sort_entries_list_recursively(((t_entry *)i->data)->entries_list, args);
    }
}

void mx_print_directory_content_recursively(t_entry directory) {
    mx_printstr(directory.relative_path);
    mx_printstr(":\n");
    for (t_list *i = directory.entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        mx_printstr(entry.dirent->d_name);
        mx_printchar('\n');
    }
    mx_printchar('\n');
    for (t_list *i = directory.entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        if (S_ISDIR(entry.stat.st_mode) && mx_strcmp(entry.dirent->d_name, ".") != 0 && mx_strcmp(entry.dirent->d_name, "..") != 0) {
            mx_print_directory_content_recursively(entry);
        }
    }
}

void mx_free_main_variables(t_args args, t_list *entries_list) {
    for (t_list *node = entries_list; node != NULL; node = node->next) {
        t_entry *entry = (t_entry *)node->data;
        mx_free_entry_ptr(&entry);
    }
    mx_clear_list(&entries_list);
    mx_free_args(args);
}

