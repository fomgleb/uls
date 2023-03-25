#include "../../../inc/utils.h"


size_t mx_print_entry_name(t_entry *entry, bool colorized) {
    if (colorized) {
        mode_t mode = entry->stat.st_mode;
        if (S_ISDIR(mode)) {
            mx_printstr("\x1b[1;36m");
        } else if (S_ISLNK(mode)) {
            mx_printstr("\x1b[35m");
        } else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
            mx_printstr("\x1b[31m");
        }
    }
    size_t size_of_printed = mx_printstr(entry->dirent ? entry->dirent->d_name : entry->relative_path);
    if (colorized) {
        mx_printstr("\x1b[m");
    }
    return size_of_printed;
}
