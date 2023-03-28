#include "../../inc/uls.h"

static void free_main_variables(t_args args, t_list *entries_list) {
    for (t_list *node = entries_list; node != NULL; node = node->next) {
        t_entry *entry = (t_entry *)node->data;
        mx_free_entry_ptr(&entry);
    }
    mx_clear_list(&entries_list);
    mx_free_args(args);
}

static int prepare_args(t_args *args, const char *existing_args) {
    t_args_error args_error = mx_validate_args(args, existing_args);

    mx_print_args_error(args_error, existing_args);
    if (args_error.error_code == ILLEGAL_FLAG) {
        free_main_variables(*args, NULL);
        exit(EXIT_FAILURE);
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

    return args_error.error_code ? 1 : 0;
}

static t_list *find_entries_list(t_list *input_entry_names_list, t_flags *flags) {
    t_list *entries_list = NULL;

    for (t_list *node = input_entry_names_list; node != NULL; node = node->next) {
        mx_push_front(&entries_list, mx_create_entry_ptr(node->data));
    }

    if (flags->d) {
        return entries_list;
    } else if (flags->R) {
        for (t_list *i = entries_list; i != NULL; i = i->next) {
            t_entry *entry = (t_entry *)i->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory_recursively(*entry, flags->a || flags->A || flags->f, !flags->a && flags->A && !flags->f);
            }
        }
    } else {
        for (t_list *node = entries_list; node != NULL; node = node->next) {
            t_entry *entry = (t_entry *)node->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory(*entry, flags->a || flags->A || flags->f, !flags->a && flags->A && !flags->f);
            }
        }
    }

    return entries_list;
}

static void mx_sort_entries_list_recursively(t_list *entries_list, t_flags *flags) {
    if (flags->f) {
        return;
    } else if (flags->S) {
        mx_sort_list(entries_list, mx_sort_entries_by_size);
    } else if (flags->t) {
        if (flags->u > flags->U && flags->u > flags->c) {
            mx_sort_list(entries_list, mx_sort_entries_by_last_access);
        } else if (flags->U > flags->u && flags->U > flags->c) {
            mx_sort_list(entries_list, mx_sort_entries_by_creation_time);
        } else if (flags->c) {
            mx_sort_list(entries_list, mx_sort_entries_by_last_access);
        } else {
            mx_sort_list(entries_list, mx_sort_entries_by_last_modification);
        }
    } else {
        mx_sort_list(entries_list, mx_sort_entries_by_name);
    }

    if (flags->r) {
        mx_reverse_list(entries_list);
    }

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        mx_sort_entries_list_recursively(((t_entry *)i->data)->entries_list, flags);
    }
}

int main(c_int argc, c_str_arr argv) {
    const char *EXISTING_FLAGS = "ACGRSU@acdflrtu1";

    t_args args = mx_convert_to_args(argc, (const char **)argv);
    int error_code = prepare_args(&args, EXISTING_FLAGS);
    t_flags flags = mx_create_flags(args.flags_str);
    t_list *entries_list = find_entries_list(args.entry_names_list, &flags);
    mx_sort_entries_list_recursively(entries_list, &flags);
    mx_print_files_and_directories(entries_list, &flags);

    free_main_variables(args, entries_list);

    return error_code;
}
