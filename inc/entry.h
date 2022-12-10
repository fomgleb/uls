#pragma once

#include "base_includes.h"
#include "path.h"

typedef struct s_entry {
    char *relative_path;
    struct dirent dirent;
    struct stat stat;
    t_list *entries_list;
} t_entry;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);
void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

t_list *mx_get_entries_in_directory(t_entry directory, bool ignore_entries_starting_with_dot);

