#include "../../inc/uls.h"

t_args_error mx_validate_args(const t_args *const restrict args, const char *const restrict existing_flags) {
    t_args_error args_error = mx_create_args_error();

    if (args->flags_str != NULL) {
        for (int i = 0; args->flags_str[i] != '\0'; i++) {
            if (mx_strchr(existing_flags, args->flags_str[i]) == NULL) {
                args_error.error_code = ILLEGAL_FLAG;
                args_error.illegal_flag = args->flags_str[i];
                return args_error;
            }
        }
    }

    struct stat stat_buffer;
    for (t_list *node = args->entry_names_list; node != NULL; node = node->next) {
        errno = 0;
        stat(node->data, &stat_buffer);
        if (errno != 0) {
            args_error.error_code = NON_EXISTENT_ENTRY;
            mx_push_front(&args_error.invalid_entry_names_list, mx_strdup(node->data));
        }    
    }

    return args_error;
}

