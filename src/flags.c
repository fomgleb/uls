#include "../inc/uls.h"

t_flags mx_create_flags(char *flags_str) {
    t_flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (flags_str != NULL) {
        flags.A = mx_strchr_last(flags_str, 'A') == NULL ? 0 : mx_strchr_last(flags_str, 'A') - flags_str + 1;
        flags.R = mx_strchr_last(flags_str, 'R') == NULL ? 0 : mx_strchr_last(flags_str, 'R') - flags_str + 1;
        flags.a = mx_strchr_last(flags_str, 'a') == NULL ? 0 : mx_strchr_last(flags_str, 'a') - flags_str + 1;
        flags.d = mx_strchr_last(flags_str, 'd') == NULL ? 0 : mx_strchr_last(flags_str, 'd') - flags_str + 1;
        flags.S = mx_strchr_last(flags_str, 'S') == NULL ? 0 : mx_strchr_last(flags_str, 'S') - flags_str + 1;
        flags.U = mx_strchr_last(flags_str, 'U') == NULL ? 0 : mx_strchr_last(flags_str, 'U') - flags_str + 1;
        flags.f = mx_strchr_last(flags_str, 'f') == NULL ? 0 : mx_strchr_last(flags_str, 'f') - flags_str + 1;
        flags.r = mx_strchr_last(flags_str, 'r') == NULL ? 0 : mx_strchr_last(flags_str, 'r') - flags_str + 1;
        flags.t = mx_strchr_last(flags_str, 't') == NULL ? 0 : mx_strchr_last(flags_str, 't') - flags_str + 1;
        flags.u = mx_strchr_last(flags_str, 'u') == NULL ? 0 : mx_strchr_last(flags_str, 'u') - flags_str + 1;
        flags.one = mx_strchr_last(flags_str, '1') == NULL ? 0 : mx_strchr_last(flags_str, '1') - flags_str + 1;
        flags.at = mx_strchr_last(flags_str, '@') == NULL ? 0 : mx_strchr_last(flags_str, '@') - flags_str + 1;
        flags.C = mx_strchr_last(flags_str, 'C') == NULL ? 0 : mx_strchr_last(flags_str, 'C') - flags_str + 1;
        flags.G = mx_strchr_last(flags_str, 'G') == NULL ? 0 : mx_strchr_last(flags_str, 'G') - flags_str + 1;
        flags.T = mx_strchr_last(flags_str, 'T') == NULL ? 0 : mx_strchr_last(flags_str, 'T') - flags_str + 1;
        flags.c = mx_strchr_last(flags_str, 'c') == NULL ? 0 : mx_strchr_last(flags_str, 'c') - flags_str + 1;
        flags.e = mx_strchr_last(flags_str, 'e') == NULL ? 0 : mx_strchr_last(flags_str, 'e') - flags_str + 1;
        flags.g = mx_strchr_last(flags_str, 'g') == NULL ? 0 : mx_strchr_last(flags_str, 'g') - flags_str + 1;
        flags.h = mx_strchr_last(flags_str, 'h') == NULL ? 0 : mx_strchr_last(flags_str, 'h') - flags_str + 1;
        flags.l = mx_strchr_last(flags_str, 'l') == NULL ? 0 : mx_strchr_last(flags_str, 'l') - flags_str + 1;
        flags.m = mx_strchr_last(flags_str, 'm') == NULL ? 0 : mx_strchr_last(flags_str, 'm') - flags_str + 1;
        flags.o = mx_strchr_last(flags_str, 'o') == NULL ? 0 : mx_strchr_last(flags_str, 'o') - flags_str + 1;
        flags.p = mx_strchr_last(flags_str, 'p') == NULL ? 0 : mx_strchr_last(flags_str, 'p') - flags_str + 1;
    }
    return flags;
}
