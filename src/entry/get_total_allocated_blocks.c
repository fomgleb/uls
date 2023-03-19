#include "../../inc/entry.h"

long int mx_get_total_allocated_blocks(t_list *entries_list) {
    long int total_allocated_blocks = 0;
    for (t_list *i = entries_list; i != NULL; i = i->next) {
        total_allocated_blocks += (*(t_entry *)i->data).stat.st_blocks;
    }
#ifdef __linux__
    total_allocated_blocks /= 2;
#endif /* __linux__ */
    return total_allocated_blocks;
}

