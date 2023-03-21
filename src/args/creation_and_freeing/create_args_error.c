#include "../../../inc/args.h"

t_args_error mx_create_args_error(void) {
    t_args_error args_error = {
        .error_code = NO_ERRORS,
        .invalid_entry_names_list = NULL,
        .illegal_flag = '\0'
    };
    return args_error;
}

