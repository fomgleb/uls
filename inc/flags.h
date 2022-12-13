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

t_selection_flags mx_create_selection_flags(char *flags_str);
t_sorting_flags mx_create_sorting_flags(char *flags_str);
t_printing_flags mx_create_printing_flags(char *flags_str);
t_flags mx_create_flags(char *flags_str);

