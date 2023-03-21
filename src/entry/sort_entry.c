#include "../../inc/uls.h"

bool mx_sort_entries_by_name(void *a, void *b) {
    t_entry a_entry = *(t_entry *)a;
    t_entry b_entry = *(t_entry *)b;
    if (a_entry.dirent == NULL  || b_entry.dirent == NULL) {
        return mx_strcmp(a_entry.relative_path, b_entry.relative_path) > 0;
    }
    return mx_strcmp(a_entry.dirent->d_name, b_entry.dirent->d_name) > 0;
}

bool mx_sort_entries_by_size(void *a, void *b) {
    time_t a_size = (*(t_entry *)a).stat.st_size;
    time_t b_size = (*(t_entry *)b).stat.st_size;
    return  a_size == b_size ?
            mx_sort_entries_by_name(a, b) :
            a_size < b_size;
}

bool mx_sort_entries_by_last_modification(void *a, void *b) {
    time_t a_last_modification_time = (*(t_entry *)a).stat.st_mtime;
    time_t b_last_modification_time = (*(t_entry *)b).stat.st_mtime;
    return  a_last_modification_time == b_last_modification_time ?
            mx_sort_entries_by_name(a, b) :
            a_last_modification_time < b_last_modification_time;
}

bool mx_sort_entries_by_last_access(void *a, void *b) {
    time_t a_last_access_time = (*(t_entry *)a).stat.st_atime;
    time_t b_last_access_time = (*(t_entry *)b).stat.st_atime;
    return  a_last_access_time == b_last_access_time ?
            mx_sort_entries_by_name(a, b) :
            a_last_access_time < b_last_access_time;
}

bool mx_sort_entries_by_creation_time(void *a, void *b) {
#ifdef __APPLE__
    time_t a_creation_time = (*(t_entry *)a).stat.st_birthtimespec.tv_sec;
    time_t b_creation_time = (*(t_entry *)b).stat.st_birthtimespec.tv_sec;
#endif
#ifdef __linux__
    time_t a_creation_time = (*(t_entry *)a).stat.st_ctime;
    time_t b_creation_time = (*(t_entry *)b).stat.st_ctime;
#endif
    return  a_creation_time == b_creation_time ?
            mx_sort_entries_by_name(a, b) :
            a_creation_time < b_creation_time;
}

bool mx_reverse_entries(void *a, void *b) {
    if (mx_strcmp((*(t_entry *)a).relative_path, (*(t_entry *)b).relative_path) != 0) {
        return true;
    }
    return false;
}

