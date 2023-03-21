#pragma once

#include "base_includes.h"
#include "flags.h"
#include "calculate_column_sizes.h"

typedef struct s_entry {
    char *relative_path;
    struct dirent *dirent;
    struct stat stat;
    t_list *entries_list;
} t_entry;

typedef enum e_output_format {
    ONE_ENTRY_PER_LINE_OUTPUT_FORMAT,
    MULTI_COLUMN_OUTPUT_FORMAT,
    LONG_OUTPUT_FORMAT
} t_output_format;

typedef enum e_print_entries_flags {
    COLORIZED_OUTPUT = 2,
} t_print_entries_flags;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);

void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags);
void mx_print_long_formatted_entry(t_entry entry, size_t *column_sizes);

t_list *mx_get_entries_in_directory(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);
t_list *mx_get_entries_in_directory_recursively(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);

char *mx_get_permissions_str(mode_t file_mode, char *path_to_file);
long int mx_get_total_allocated_blocks(t_list *entries_list);

bool mx_sort_entries_by_name(void *a, void *b);
bool mx_sort_entries_by_size(void *a, void *b);
bool mx_sort_entries_by_last_modification(void *a, void *b);
bool mx_sort_entries_by_last_access(void *a, void *b);
bool mx_sort_entries_by_creation_time(void *a, void *b);
bool mx_reverse_entries(void *a, void *b);
