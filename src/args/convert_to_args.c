#include "../../inc/uls.h"

t_args mx_convert_to_args(const int argc, const char *const*const argv) {
    t_args new_args = mx_create_args();

    int argv_index = 1;
    for (; argv_index < argc && argv[argv_index][0] == '-' && argv[argv_index][1] != '\0'; argv_index++) {
        char *new_flags = mx_strjoin(new_args.flags_str, argv[argv_index] + 1);
        free(new_args.flags_str);
        new_args.flags_str = new_flags;
    }

    for (; argv_index < argc; argv_index++) {
        mx_push_front(&new_args.entry_names_list, mx_strdup(argv[argv_index]));
    }

    if (new_args.entry_names_list == NULL) {
        mx_push_front(&new_args.entry_names_list, mx_strdup("."));
    }

    return new_args;
}

