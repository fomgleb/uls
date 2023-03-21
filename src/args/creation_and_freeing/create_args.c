#include "../../../inc/args.h"

t_args mx_create_args(void) {
    t_args new_args = {
        .entry_names_list = NULL,
        .flags_str = NULL
    };
    return new_args;
}

