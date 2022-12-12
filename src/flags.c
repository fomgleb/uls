#include "../inc/flags.h"

t_selection_flags mx_create_selection_flags(char *flags_str) {
    t_selection_flags selection_flags = {false, false, false, false};
    if (flags_str != NULL) {
        selection_flags.A = mx_strchr_last(flags_str, 'A') == NULL ? 0 : mx_strchr_last(flags_str, 'A') - flags_str + 1;
        selection_flags.R = mx_strchr_last(flags_str, 'R') == NULL ? 0 : mx_strchr_last(flags_str, 'R') - flags_str + 1;
        selection_flags.a = mx_strchr_last(flags_str, 'a') == NULL ? 0 : mx_strchr_last(flags_str, 'a') - flags_str + 1;
        selection_flags.d = mx_strchr_last(flags_str, 'd') == NULL ? 0 : mx_strchr_last(flags_str, 'd') - flags_str + 1;
    }
    return selection_flags;
}

t_sorting_flags mx_create_sorting_flags(char *flags_str) {
    t_sorting_flags sorting_flags = {false, false, false, false, false, false, false};
    if (flags_str != NULL) {
        sorting_flags.S = mx_strchr_last(flags_str, 'S') == NULL ? 0 : mx_strchr_last(flags_str, 'S') - flags_str + 1;
        sorting_flags.U = mx_strchr_last(flags_str, 'U') == NULL ? 0 : mx_strchr_last(flags_str, 'U') - flags_str + 1;
        sorting_flags.c = mx_strchr_last(flags_str, 'c') == NULL ? 0 : mx_strchr_last(flags_str, 'c') - flags_str + 1;
        sorting_flags.f = mx_strchr_last(flags_str, 'f') == NULL ? 0 : mx_strchr_last(flags_str, 'f') - flags_str + 1;
        sorting_flags.r = mx_strchr_last(flags_str, 'r') == NULL ? 0 : mx_strchr_last(flags_str, 'r') - flags_str + 1;
        sorting_flags.t = mx_strchr_last(flags_str, 't') == NULL ? 0 : mx_strchr_last(flags_str, 't') - flags_str + 1;
        sorting_flags.u = mx_strchr_last(flags_str, 'u') == NULL ? 0 : mx_strchr_last(flags_str, 'u') - flags_str + 1;
    }
    return sorting_flags;
}

