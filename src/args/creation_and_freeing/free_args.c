#include "../../../inc/args.h"

void mx_free_args(t_args args) {
    for (t_list *node = args.entry_names_list; node != NULL; node = node->next) {
        char *entry_name = (char *)node->data;
        free(entry_name);
    }
    mx_clear_list(&args.entry_names_list);
    free(args.flags_str);
}

