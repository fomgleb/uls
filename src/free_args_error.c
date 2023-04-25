#include "../inc/uls.h"

void mx_free_args_error(t_args_error args_error) {
    for (t_list *node = args_error.invalid_entry_names_list; node != NULL; node = node->next) {
        free(node->data);
    }
    mx_clear_list(&args_error.invalid_entry_names_list);
}
