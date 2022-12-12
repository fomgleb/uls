#pragma once

#include "base_includes.h"
#include "args.h"

typedef struct s_selection_flags {
    bool A;
    bool R;
    bool a;
    bool d;
} t_selection_flags;

typedef struct s_sorting_flags {
    bool S;
    bool U;
    bool c;
    bool f;
    bool r;
    bool t;
    bool u;
} t_sorting_flags;

t_selection_flags mx_create_selection_flags(char *flags_str);
t_sorting_flags mx_create_sorting_flags(char *flags_str);

