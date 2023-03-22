#pragma once

#include "../libmx/inc/libmx.h"
#include "utils.h"
#include <errno.h>
#include <math.h>
#include <time.h>

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

typedef enum e_output_format {
    ONE_ENTRY_PER_LINE_OUTPUT_FORMAT,
    MULTI_COLUMN_OUTPUT_FORMAT,
    LONG_OUTPUT_FORMAT
} t_output_format;

typedef enum e_print_entries_flags {
    COLORIZED_OUTPUT = 2,
    RECURSIVE_OUTPUT = 4
} t_print_entries_flags;

typedef struct s_selection_flags {
    unsigned int A;
    unsigned int R;
    unsigned int a;
    unsigned int d;
} t_selection_flags;

typedef struct s_sorting_flags {
    unsigned int S;
    unsigned int U;
    unsigned int c;
    unsigned int f;
    unsigned int r;
    unsigned int t;
    unsigned int u;
} t_sorting_flags;

typedef struct s_printing_flags {
    unsigned int one; // 1
    unsigned int at; // @
    unsigned int C;
    unsigned int G;
    unsigned int T;
    unsigned int c;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    unsigned int l;
    unsigned int m;
    unsigned int o;
    unsigned int p;
} t_printing_flags;

typedef struct s_flags {
    unsigned int A;
    unsigned int R;
    unsigned int a;
    unsigned int d;

    unsigned int S;
    unsigned int U;
    unsigned int f;
    unsigned int r;
    unsigned int t;
    unsigned int u;

    unsigned int one; // 1
    unsigned int at; // @
    unsigned int C;
    unsigned int G;
    unsigned int T;
    unsigned int c;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    unsigned int l;
    unsigned int m;
    unsigned int o;
    unsigned int p;
} t_flags;

#define NON_EXISTENT_ENTRY_MESSAGE "No such file or directory"
#define PROGRAM_NAME "uls"

t_args mx_create_args(void);
void mx_free_args(t_args args);

t_args mx_convert_to_args(const int argc, const char *const*const argv);
void mx_print_args_error(t_args_error args_error, const char *existing_flags);

t_args_error mx_create_args_error(void);
void mx_free_args_error(t_args_error args_error);
t_args_error mx_validate_args(const t_args *const restrict args, const char *const restrict existing_flags);

t_selection_flags mx_create_selection_flags(char *flags_str);
t_sorting_flags mx_create_sorting_flags(char *flags_str);
t_printing_flags mx_create_printing_flags(char *flags_str);
t_flags mx_create_flags(char *flags_str);

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags);