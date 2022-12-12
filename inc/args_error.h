#pragma once

#include "base_includes.h"
#include "base_defines.h"
#include "args.h"

typedef enum e_args_error_code {
    NO_ERRORS,
    ILLEGAL_FLAG,
    NON_EXISTENT_ENTRY
} t_args_error_code;

typedef struct s_args_error {
    t_args_error_code error_code;
    t_list *invalid_entry_names_list;
    char illegal_flag;
} t_args_error;

t_args_error mx_create_args_error(void);
void mx_free_args_error(t_args_error args_error);

t_args_error mx_validate_args(t_args args, const char *existing_flags);
void mx_print_args_error(t_args_error args_error, const char *existing_flags);

