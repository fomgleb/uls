#include "../../inc/uls.h"

static int prepare_args(t_args *args, c_str existing_args) {
    t_args_error args_error = mx_validate_args(args, existing_args);

    mx_print_args_error(args_error, existing_args);
    if (args_error.error_code == ILLEGAL_FLAG) {
        mx_free_args(*args);
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

int main(c_int argc, c_str_arr argv) {
    c_str EXISTING_FLAGS = "ACGRSTU@acdfhlprtu1";

    t_args args = mx_convert_to_args(argc, argv);
    int error_code = prepare_args(&args, EXISTING_FLAGS);
    t_flags flags = mx_create_flags(args.flags_str);
    t_list *entries_list = mx_find_entries_list(args.entry_names_list, &flags);
    mx_sort_entries_list_recursively(entries_list, &flags);
    mx_print_files_and_directories(entries_list, &flags);

    mx_free_entries_list(entries_list);
    mx_free_args(args);

    return error_code;
}
