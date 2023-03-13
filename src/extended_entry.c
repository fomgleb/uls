#include "../inc/extended_entry.h"

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

char mx_get_file_type_symbol(mode_t file_mode) {
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

char *mx_get_permissions_str(mode_t file_mode, char *path_to_file) {
    static const char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

    char *permissions_str = mx_strnew(11);

    permissions_str[0] = mx_get_file_type_symbol(file_mode);
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
    bool has_xattr = listxattr(path_to_file, NULL, 1000, 0) > 0;
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

unsigned long int mx_get_number_of_links(t_entry entry) {
    return entry.stat.st_nlink;
}

char *mx_get_owner_name(uid_t user_id) {
    struct passwd *owner_information = getpwuid(user_id);
    return mx_strdup(owner_information->pw_name);
}

char *mx_get_group_name(gid_t group_id) {
    struct group *group_information = getgrgid(group_id);
    return mx_strdup(group_information->gr_name);
}

long int mx_get_number_of_bytes(struct stat *stat_ptr) {
    return stat_ptr->st_size;
}

// char *mx_get_month(t_entry *entry_ptr) {
    
// }
