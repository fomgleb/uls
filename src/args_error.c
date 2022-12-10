#include "../inc/args_error.h"

t_args_error mx_create_args_error(void) {
    t_args_error args_error;
    args_error.error_code = NO_ERRORS;
    args_error.invalid_entry_names_list = NULL;
    args_error.illegal_flag = '\0';
    return args_error;
}

void mx_free_args_error(t_args_error args_error) {
    for (t_list *node = args_error.invalid_entry_names_list; node != NULL; node = node->next) {
        free(node->data);
    }
    mx_clear_list(&args_error.invalid_entry_names_list);
}

t_args_error mx_validate_args(t_args args, const char *existing_flags) {
    t_args_error args_error = mx_create_args_error();

    if (args.flags != NULL) {
        for (int i = 0; args.flags[i] != '\0'; i++) {
            if (mx_strchr(existing_flags, args.flags[i]) == NULL) {
                args_error.error_code = ILLEGAL_FLAG;
                args_error.illegal_flag = args.flags[i];
                return args_error;
            }
        }
    }

    struct stat stat_buffer;
    for (t_list *node = args.entry_names_list; node != NULL; node = node->next) {
        errno = 0;
        stat(node->data, &stat_buffer);
        if (errno != 0) {
            args_error.error_code = NON_EXISTENT_ENTRY;
            mx_push_front(&args_error.invalid_entry_names_list, mx_strdup(node->data));
            return args_error;
        }    
    }

    args_error.error_code = NO_ERRORS;
    return args_error;
}

void mx_print_args_error(t_args_error args_error) {
    if (args_error.error_code == NON_EXISTENT_ENTRY) {
        for (t_list *node = args_error.invalid_entry_names_list; node != NULL; node = node->next) {
            mx_printerr(PROGRAM_NAME);
            mx_printerr(": ");
            mx_printerr(node->data);
            mx_printerr(": ");
            mx_printerr(NON_EXISTENT_ENTRY_MESSAGE);
            mx_printerr("\n");
        }
    } else if (args_error.error_code == ILLEGAL_FLAG) {
        mx_printerr("uls: illegal option -- ");
        mx_printerr(&args_error.illegal_flag);
        mx_printerr(USAGE_MESSAGE);
    }
}

