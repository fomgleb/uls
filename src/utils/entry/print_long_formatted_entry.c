#include "../../../inc/utils.h"

static char get_file_type_symbol(mode_t file_mode) {
    if (S_ISBLK(file_mode)) {
        return 'b';
    } else if (S_ISCHR(file_mode)) {
        return 'c';
    } else if (S_ISDIR(file_mode)) {
        return 'd';
// #ifdef S_ISLNK
    } else if (S_ISLNK(file_mode)) {
        return 'l';
// #endif /* S_ISLNK */
#ifdef S_ISSOCK
    } else if (S_ISSOCK(file_mode)) {
        return 's';
#endif /* S_ISSOCK */
#ifdef S_ISFIFO
    } else if (S_ISFIFO(file_mode)) {
        return 'p';
#endif /* S_ISFIFO */
    } else if (S_ISREG(file_mode)) {
        return '-';
    }
    return '?';
}

static char *get_permissions_str(mode_t file_mode, char *path_to_file) {
    static const char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

    char *permissions_str = mx_strnew(11);

    permissions_str[0] = get_file_type_symbol(file_mode);
    mx_strcpy(&permissions_str[1], rwx[(file_mode >> 6) & 7]);
    mx_strcpy(&permissions_str[4], rwx[(file_mode >> 3) & 7]);
    mx_strcpy(&permissions_str[7], rwx[file_mode & 7]);
    if (file_mode & S_ISUID)
        permissions_str[3] = (file_mode & S_IXUSR) ? 's' : 'S';
    if (file_mode & S_ISGID)
        permissions_str[6] = (file_mode & S_IXGRP) ? 's' : 'l';
#ifdef S_ISVTX
    if (file_mode & S_ISVTX)
        permissions_str[9] = (file_mode & S_IXOTH) ? 't' : 'T';
#endif /* S_ISVTX */
#ifdef __APPLE__
    bool has_xattr = listxattr(path_to_file, NULL, 10000, XATTR_NOFOLLOW) > 0;
#endif /* __APPLE__ */
#ifdef __linux__
    bool has_xattr = listxattr(path_to_file, NULL, 1000) > 0;
#endif /* __linux__ */
#ifdef __APPLE__
    bool has_acl = acl_get_file(path_to_file, ACL_TYPE_EXTENDED);
#endif /* __APPLE__ */
    if (has_xattr) {
        permissions_str[10] = '@';
#ifdef __APPLE__
    } else if (has_acl) {
        permissions_str[10] = '+';
#endif /* __APPLE__ */
    } else {
        permissions_str[10] = ' ';
    }

    return permissions_str;
}

static void print_entry_permissions_with_indent(t_entry *entry) {
    char *permissions_str = get_permissions_str(entry->stat.st_mode, entry->relative_path);
    mx_printstr(permissions_str);
    free(permissions_str);
    mx_printchar(' ');
}

static void print_number_of_entry_links_with_indent(t_entry *entry, size_t column_size) {
    int indent = column_size - mx_get_digits_count(entry->stat.st_nlink);
    mx_printnchar(' ', indent);
    mx_printint(entry->stat.st_nlink);
    mx_printchar(' ');
}

static void print_owner_name_with_indent(t_entry *entry, size_t column_size) {
    mx_printstr(getpwuid(entry->stat.st_uid)->pw_name);
    mx_printnchar(' ', column_size - mx_strlen(getpwuid(entry->stat.st_uid)->pw_name));
    mx_printnchar(' ', 2);
}

static void print_group_name_with_indent(t_entry *entry, size_t column_size) {
    mx_printstr(getgrgid(entry->stat.st_gid)->gr_name);
    mx_printnchar(' ', column_size - mx_strlen(getgrgid(entry->stat.st_gid)->gr_name));
    mx_printnchar(' ', 2);
}

static void print_number_of_entry_bytes(t_entry *entry, size_t column_size) {
    mx_printnchar(' ', column_size - mx_get_digits_count(entry->stat.st_size));
    mx_printint(entry->stat.st_size);
    mx_printchar(' ');
}

static void print_month_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 4, 3);
    mx_printchar(' ');
}

static void print_month_day_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 8, 2);
    mx_printchar(' ');
}

static void print_hours_and_minutes_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 11, 5);
    mx_printchar(' ');
}

static void print_year_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 19, 5);
    mx_printchar(' ');
}

static void print_link_content(t_entry entry) {
    char link_content[1024];
    ssize_t link_content_len = readlink(entry.relative_path, link_content, 1024);
    mx_printnstr(link_content, link_content_len);
}

static time_t calculate_difference_between_times(time_t time1, time_t time2) {
    if (time1 > time2) {
        return time1 - time2;
    } else {
        return time2 - time1;
    }
}

void mx_print_long_formatted_entry(t_entry entry, size_t *column_sizes) {
    print_entry_permissions_with_indent(&entry);
    print_number_of_entry_links_with_indent(&entry, column_sizes[0]);
    print_owner_name_with_indent(&entry, column_sizes[1]);
    print_group_name_with_indent(&entry, column_sizes[2]);
    print_number_of_entry_bytes(&entry, column_sizes[3]);
    char *human_readable_time = ctime(&entry.stat.st_mtime);
    print_month_with_indent(human_readable_time);
    print_month_day_with_indent(human_readable_time);
    if (calculate_difference_between_times(entry.stat.st_mtime, time(NULL)) > SECONDS_IN_HALF_YEAR) {
        print_year_with_indent(human_readable_time);
    } else {
        print_hours_and_minutes_with_indent(human_readable_time);
    }
    mx_printstr(entry.dirent != NULL ? entry.dirent->d_name : entry.relative_path);
    if (S_ISLNK(entry.stat.st_mode)) {
        mx_printstr(" -> ");
        print_link_content(entry);
    }
    mx_printchar('\n');
}
