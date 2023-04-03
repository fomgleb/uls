#include "../../inc/uls.h"

int main(c_int argc, c_str_arr argv) {
    c_str EXISTING_FLAGS = "ACGRSTU@acdefghlmoprtu1";

    c_args args = mx_convert_to_args(argc, argv);
    t_args_error args_error = mx_validate_args(&args, EXISTING_FLAGS);
    mx_print_args_error(args_error, EXISTING_FLAGS);
    if (args_error.error_code != ILLEGAL_FLAG) {
        t_flags flags = mx_create_flags(args.flags_str);
        t_list *entries_list = mx_find_entries_list(args.entry_names_list, args_error.invalid_entry_names_list, &flags);
        mx_sort_entries_list_recursively(entries_list, &flags);
        mx_print_files_and_directories(entries_list, &flags, mx_list_size(args_error.invalid_entry_names_list));
        mx_free_entries_list(entries_list);
    }

    mx_free_args(args);
    mx_free_args_error(args_error);

    return args_error.error_code ? 1 : 0;
}
