#pragma once

#include "base_includes.h"

typedef struct s_args {
    t_list *entry_names_list;
    char *flags_str;
} t_args;

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

#define NON_EXISTENT_ENTRY_MESSAGE "No such file or directory"
#define PROGRAM_NAME "uls"

t_args mx_convert_to_args(const int argc, const char *const*const argv);

t_args_error mx_create_args_error(void);
t_args mx_create_args(void);

void mx_free_args_error(t_args_error args_error);
void mx_free_args(t_args args); 

void mx_print_args_error(t_args_error args_error, const char *existing_flags);

t_args_error mx_validate_args(const t_args *const restrict args, const char *const restrict existing_flags);
