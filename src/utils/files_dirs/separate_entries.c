#include "../../../inc/utils.h"

static t_files_dirs create_files_dirs(void) {
    t_files_dirs files_dirs = {
        .files_list = NULL,
        .dirs_list = NULL,
        .total_entries_count = 0
    };
    return files_dirs;
}

t_files_dirs mx_separate_entries(t_list *entries_list, c_bool follow_link) {
    t_files_dirs files_dirs = create_files_dirs();

    for (t_list *i = entries_list; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;
        if (S_ISDIR(entry.stat.st_mode)) {
            mx_push_back(&files_dirs.dirs_list, i->data);
        } else if (follow_link) {
            struct stat followed_link_stat;
            stat(entry.relative_path, &followed_link_stat);
            if (S_ISDIR(followed_link_stat.st_mode)) {
                mx_push_back(&files_dirs.dirs_list, i->data);
            }
        } else {
            mx_push_back(&files_dirs.files_list, i->data);
        }
        files_dirs.total_entries_count++;
    }

    return files_dirs;
}
