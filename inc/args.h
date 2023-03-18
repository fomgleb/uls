#pragma once

#include "base_includes.h"

typedef struct s_args {
    t_list *entry_names_list;
    char *flags_str;
} t_args;

t_args mx_create_args(void);
void mx_free_args(t_args args); 
t_args mx_convert_to_args(int argc, char **argv);
