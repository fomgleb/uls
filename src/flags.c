#include "../inc/flags.h"

t_selection_flags mx_create_selection_flags(char *flags_str) {
    t_selection_flags selection_flags = {false, false, false, false};
    if (flags_str != NULL) {
        selection_flags.A = mx_strchr(flags_str, 'A') != NULL;
        selection_flags.R = mx_strchr(flags_str, 'R') != NULL;
        selection_flags.a = mx_strchr(flags_str, 'a') != NULL;
        selection_flags.d = mx_strchr(flags_str, 'd') != NULL;
    }
    return selection_flags;
}

t_sorting_flags mx_create_sorting_flags(char *flags_str) {
    t_sorting_flags sorting_flags = {false, false, false, false, false, false, false};
    if (flags_str != NULL) {
        sorting_flags.S = mx_strchr(flags_str, 'S') != NULL;
        sorting_flags.U = mx_strchr(flags_str, 'U') != NULL;
        sorting_flags.c = mx_strchr(flags_str, 'c') != NULL;
        sorting_flags.f = mx_strchr(flags_str, 'f') != NULL;
        sorting_flags.r = mx_strchr(flags_str, 'r') != NULL;
        sorting_flags.t = mx_strchr(flags_str, 't') != NULL;
        sorting_flags.u = mx_strchr(flags_str, 'u') != NULL;
    }
    return sorting_flags;
}

