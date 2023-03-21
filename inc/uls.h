#pragma once

#include "../libmx/inc/libmx.h"
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#ifdef __APPLE__
#include <sys/acl.h>
#endif
#include <sys/xattr.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdbool.h>

typedef struct s_args {
    t_list *entry_names_list;
    char *flags_str;
} t_args;
typedef enum e_args_error_code {
    NO_ERRORS,
    ILLEGAL_FLAG,
    NON_EXISTENT_ENTRY
} t_args_error_code;
typedef struct s_args_error {
    t_args_error_code error_code;
    t_list *invalid_entry_names_list;
    char illegal_flag;
} t_args_error;
#define NON_EXISTENT_ENTRY_MESSAGE "No such file or directory"
#define PROGRAM_NAME "uls"
t_args mx_convert_to_args(const int argc, const char *const*const argv);
t_args_error mx_create_args_error(void);
t_args mx_create_args(void);
void mx_free_args_error(t_args_error args_error);
void mx_free_args(t_args args); 
void mx_print_args_error(t_args_error args_error, const char *existing_flags);
t_args_error mx_validate_args(const t_args *const restrict args, const char *const restrict existing_flags);

#define SECONDS_IN_HALF_YEAR 15768000
size_t *mx_calculate_long_format_column_sizes(t_list *entries);

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
typedef enum e_output_format {
    ONE_ENTRY_PER_LINE_OUTPUT_FORMAT,
    MULTI_COLUMN_OUTPUT_FORMAT,
    LONG_OUTPUT_FORMAT
} t_output_format;
typedef enum e_print_entries_flags {
    COLORIZED_OUTPUT = 2,
    RECURSIVE_OUTPUT = 4
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
t_files_dirs mx_separate_entries(t_list *entries_list);

typedef struct s_selection_flags {
    unsigned int A;
    unsigned int R;
    unsigned int a;
    unsigned int d;
} t_selection_flags;
typedef struct s_sorting_flags {
    unsigned int S;
    unsigned int U;
    unsigned int c;
    unsigned int f;
    unsigned int r;
    unsigned int t;
    unsigned int u;
} t_sorting_flags;
typedef struct s_printing_flags {
    unsigned int one; // 1
    unsigned int at; // @
    unsigned int C;
    unsigned int G;
    unsigned int T;
    unsigned int c;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    unsigned int l;
    unsigned int m;
    unsigned int o;
    unsigned int p;
} t_printing_flags;
typedef struct s_flags {
    unsigned int A;
    unsigned int R;
    unsigned int a;
    unsigned int d;

    unsigned int S;
    unsigned int U;
    unsigned int f;
    unsigned int r;
    unsigned int t;
    unsigned int u;

    unsigned int one; // 1
    unsigned int at; // @
    unsigned int C;
    unsigned int G;
    unsigned int T;
    unsigned int c;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    unsigned int l;
    unsigned int m;
    unsigned int o;
    unsigned int p;
} t_flags;
t_selection_flags mx_create_selection_flags(char *flags_str);
t_sorting_flags mx_create_sorting_flags(char *flags_str);
t_printing_flags mx_create_printing_flags(char *flags_str);
t_flags mx_create_flags(char *flags_str);

#define MAX2(a, b) (a > b ? a : b)
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))
