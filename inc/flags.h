#pragma once

#include "base_includes.h"
#include "args.h"

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

t_selection_flags mx_create_selection_flags(char *flags_str);
t_sorting_flags mx_create_sorting_flags(char *flags_str);

