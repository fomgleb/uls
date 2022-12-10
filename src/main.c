#include "../inc/main.h"

int main(int argc, char **argv) {
    const char *EXISTING_FLAGS = "Aad";

    t_args args = mx_convert_to_args(argc, argv);
    mx_prepare_args(&args, EXISTING_FLAGS);
    t_list *entries_list = mx_find_entries_list(args);

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
            mx_printstr(entry.relative_path);
            mx_printstr(":\n");
            for (t_list *j = entry.entries_list; j != NULL; j = j->next) {
                mx_printstr((*(t_entry *)j->data).dirent.d_name);
                mx_printchar('\n');
            }
            mx_printchar('\n');
        }
    }    

    mx_free_main_variables(args, entries_list);

    return 0;

    // Printing
    // if (main_variables.args.flags == NULL) {
    //     for (t_list *i = main_variables.entries_list; i != NULL; i = i->next) {
    //         t_entry entry = *(t_entry *)i->data;

    //     }
    //     for (t_list *i = main_variables.entries_list; i != NULL; i = i->next) {
    //         t_entry entry = *(t_entry *)i->data;
    //         mx_printstr(entry.relative_path);
    //         mx_printstr(":\n");
    //         for (t_list *j = entry.entries_list; j != NULL; j = j->next) {
    //             mx_printstr(((t_entry *)j->data)->dirent.d_name);
    //             mx_printchar('\n');
    //         }
    //         mx_printchar('\n');
    //     }
    // } else if (mx_strchr(main_variables.args.flags, 'd') != NULL) {
    //     for (t_list *node = main_variables.entries_list; node != NULL; node = node->next) {
    //         t_entry entry = *(t_entry *)node->data;
    //         mx_printstr(entry.relative_path);
    //         mx_printchar('\n');
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

void mx_prepare_args(t_args *args, const char *existing_args) {
    t_args_error args_error = mx_validate_args(*args, existing_args);

    mx_print_args_error(args_error);
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
    bool a_flag = args.flags != NULL && mx_strchr(args.flags, 'a') != NULL;
    bool A_flag = args.flags != NULL && mx_strchr(args.flags, 'A') != NULL;
    bool d_flag = args.flags != NULL && mx_strchr(args.flags, 'd') != NULL;
    bool R_flag = args.flags != NULL && mx_strchr(args.flags, 'R') != NULL;

    for (t_list *node = args.entry_names_list; node != NULL; node = node->next) {
        mx_push_front(&entries_list, mx_create_entry_ptr(node->data));
    }

    if (d_flag) {
        return entries_list;
    } else if (R_flag) {
        // Some code
    } else {
        for (t_list *node = entries_list; node != NULL; node = node->next) {
            t_entry *entry = (t_entry *)node->data;
            if (S_ISDIR(entry->stat.st_mode)) {
                entry->entries_list = mx_get_entries_in_directory(*entry, !A_flag && !a_flag);
            }
            if (A_flag && !a_flag) {
                t_list *next_j;
                for (t_list *j = entry->entries_list; j != NULL; j = next_j) {
                    next_j = j->next;
                    if (mx_strcmp(((t_entry *)j->data)->dirent.d_name, ".") == 0 ||
                    mx_strcmp(((t_entry *)j->data)->dirent.d_name, "..") == 0) {
                        t_entry *j_entry = (t_entry *)j->data;
                        mx_free_entry_ptr(&j_entry);
                        mx_pop_node(&entry->entries_list, j);
                    }
                }
            }
        }
    }

    return entries_list;
}

void mx_free_main_variables(t_args args, t_list *entries_list) {
    for (t_list *node = entries_list; node != NULL; node = node->next) {
        t_entry *entry = (t_entry *)node->data;
        mx_free_entry_ptr(&entry);
    }
    mx_clear_list(&entries_list);
    mx_free_args(args);
}

