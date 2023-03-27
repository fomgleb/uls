#pragma once

#include "../libmx/inc/libmx.h"
#include <stddef.h>
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

typedef char *str;
typedef const bool c_bool;
typedef const char c_char;
typedef const float c_float;
typedef const ushort c_ushort;
typedef const size_t c_size_t;
typedef const int c_int;
typedef const char *const c_str;
typedef const char *const *const c_str_arr;

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

typedef enum e_time_type {
    TIME_OF_LAST_DATA_MODIFICATION,
    TIME_OF_LAST_ACCESS,
    TIME_OF_LAST_FILE_STATUS_CHANGE,
    TIME_OF_FILE_CREATION
} t_time_type;
typedef const t_time_type c_time_type;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);

void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

t_list *mx_get_entries_in_directory(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);
t_list *mx_get_entries_in_directory_recursively(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory);

void mx_print_entries_in_columns(t_list *entries_list, c_char column_delimiter, ushort terminal_width, bool print_newline_in_the_end, bool colorized);
void mx_print_long_formatted_entries(t_list *entries_list, c_time_type time_type, bool print_total_number_of_512_byte_blocks, bool print_newline_in_the_end, bool colorized);
void mx_print_entries_per_line(t_list *entries_list, bool colorized, bool print_newline_in_the_end);

size_t mx_print_entry_name(t_entry *entry, bool colorized);

void mx_print_long_formatted_entry(t_entry entry, size_t *column_sizes, const t_time_type time_type, bool colorized);

bool mx_sort_entries_by_name(void *a, void *b);
bool mx_sort_entries_by_size(void *a, void *b);
bool mx_sort_entries_by_last_modification(void *a, void *b);
bool mx_sort_entries_by_last_access(void *a, void *b);
bool mx_sort_entries_by_status_change(void *a, void *b);
bool mx_sort_entries_by_creation_time(void *a, void *b);
bool mx_reverse_entries(void *a, void *b);

void free_files_dirs(t_files_dirs *files_dirs);
t_files_dirs mx_separate_entries(t_list *entries_list);

float mx_round_down(c_float number);
float mx_round_up(c_float number);

void mx_print_two_strings_if(c_bool condition, c_str string1, c_str string2);
void mx_print_two_strings(c_str string1, c_str string2);
void mx_printchar_if(c_bool condition, c_char character);
void mx_printnchar_if(c_bool condition, c_char character, c_size_t count);

ushort mx_get_terminal_width(void);
