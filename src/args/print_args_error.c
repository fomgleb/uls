#include "../../inc/uls.h"

static bool sort_strings_by_name(void *a, void *b) {
    char *a_string = (char *)a;
    char *b_string = (char *)b;
    return mx_strcmp(a_string, b_string) > 0;
}

void mx_print_args_error(t_args_error args_error, const char *existing_flags) {
    if (args_error.error_code == NON_EXISTENT_ENTRY) {
        mx_sort_list(args_error.invalid_entry_names_list, sort_strings_by_name);
        for (t_list *node = args_error.invalid_entry_names_list; node != NULL; node = node->next) {
            mx_printerr(PROGRAM_NAME);
            mx_printerr(": ");
            mx_printerr(node->data);
            mx_printerr(": ");
            mx_printerr(NON_EXISTENT_ENTRY_MESSAGE);
            mx_printerr("\n");
        }
    } else if (args_error.error_code == ILLEGAL_FLAG) {
        mx_printerr("uls: illegal option -- ");
        mx_printerrch(args_error.illegal_flag);
        mx_printerrch('\n');
        mx_printerr("usage: uls [-");
        mx_printerr(existing_flags);
        mx_printerr("] [file ...]\n");
    }
}

