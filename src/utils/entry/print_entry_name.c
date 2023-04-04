#include "../../../inc/utils.h"

size_t mx_print_entry_name(t_entry *entry, bool colorized, bool slash_after_dirs) {
    if (colorized) {
        mode_t mode = entry->stat.st_mode;
        if (S_ISDIR(mode)) {
            mx_printstr("\x1b[1;36m");
        } else if (S_ISLNK(mode)) {
            mx_printstr("\x1b[35m");
        } else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
            mx_printstr("\x1b[31m");
        } else if (S_ISSOCK(mode)) {
            mx_printstr("\x1b[32m");
        }
    }
    size_t size_of_printed = mx_printstr(entry->dirent ? entry->dirent->d_name : entry->relative_path);
    if (colorized) {
        mx_printstr("\x1b[m");
    }
    if (slash_after_dirs && S_ISDIR(entry->stat.st_mode)) {
        mx_printchar('/');
        size_of_printed++;
    }
    return size_of_printed;
}
