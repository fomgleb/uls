#pragma once

#include "../libmx/inc/libmx.h"
#include <sys/ttycom.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>

#define MAX2(a, b) (a > b ? a : b)
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))

#define SECONDS_IN_HALF_YEAR 15768000

#define str char *

#define c_bool const bool
#define c_str const str const

typedef struct s_entry {
    char *relative_path;
    struct dirent *dirent;
    struct stat stat;
    t_list *entries_list;
} t_entry;

typedef struct s_files_dirs {
    t_list *files_list;
    t_list *dirs_list;
    size_t total_entries_count;
} t_files_dirs;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);

void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

t_list *mx_get_entries_in_directory(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);
t_list *mx_get_entries_in_directory_recursively(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);

void mx_print_files_and_directories_in_columns(t_list *entries_list, bool colorized);
void mx_print_files_and_directories_per_line(t_list *entries_list, bool recursively);
void mx_print_long_formatted_files_and_directories(t_list *entries_list, bool recursive);

void mx_print_long_formatted_entry(t_entry entry, size_t *column_sizes);

bool mx_sort_entries_by_name(void *a, void *b);
bool mx_sort_entries_by_size(void *a, void *b);
bool mx_sort_entries_by_last_modification(void *a, void *b);
bool mx_sort_entries_by_last_access(void *a, void *b);
bool mx_sort_entries_by_creation_time(void *a, void *b);
bool mx_reverse_entries(void *a, void *b);

void free_files_dirs(t_files_dirs *files_dirs);
t_files_dirs mx_separate_entries(t_list *entries_list);

float mx_round_down(float number);
float mx_round_up(float number);

void mx_print_two_strings_if(c_bool condition, c_str string1, c_str string2);
void mx_print_two_strings(c_str string1, c_str string2);
void mx_printchar_if(bool condition, char character);

ushort mx_get_terminal_width();
