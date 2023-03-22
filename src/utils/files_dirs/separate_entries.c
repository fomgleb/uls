#include "../../../inc/utils.h"

static t_files_dirs create_files_dirs(void) {
    t_files_dirs files_dirs = {
        .files_list = NULL,
        .dirs_list = NULL,
        .total_entries_count = 0
    };
    return files_dirs;
}

t_files_dirs mx_separate_entries(t_list *entries_list) {
    t_files_dirs files_dirs = create_files_dirs();

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        mx_push_back(S_ISDIR(entry.stat.st_mode) ? &files_dirs.dirs_list : &files_dirs.files_list, i->data);
        files_dirs.total_entries_count++;
    }

    return files_dirs;
}

