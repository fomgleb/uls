#pragma once

#include "base_includes.h"

typedef struct s_entry {
    char *relative_path;
    struct dirent *dirent;
    struct stat stat;
    t_list *entries_list;
} t_entry;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);
void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

bool mx_sort_entries_by_name(void *a, void *b);
bool mx_sort_entries_by_size(void *a, void *b);
bool mx_sort_entries_by_last_modification(void *a, void *b);
bool mx_sort_entries_by_last_access(void *a, void *b);
bool mx_sort_entries_by_creation_time(void *a, void *b);
bool mx_reverse_entries(void *a, void *b);

t_list *mx_get_entries_in_directory(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);
t_list *mx_get_entries_in_directory_recursively(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);

