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
#define BYTES_IN_KILOBYTE 1024

typedef char *str;
typedef unsigned char uchar;
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

typedef enum e_long_format_flags {
    IS_COLORIZED = 2,
    DISPLAY_EXTENDED_ATTRIBUTES = 4,
    FULL_TIME_INFO = 8,
    HUMAN_READABLE_SIZE = 16,
    PRINT_SLASH_AFTER_DIRECTORIES = 32
} t_long_format_flags;
typedef const t_long_format_flags c_long_format_flags;

typedef enum e_find_entries_flags {
    INCLUDE_ENTRIES_STARTING_WITH_DOT = 2,
    IGNORE_CURRENT_AND_FATHER_DIRECTORY = 4
} t_find_entries_flags;

t_entry mx_create_entry(char *relative_path);
t_entry *mx_create_entry_ptr(char *relative_path);

void mx_free_entry(t_entry entry);
void mx_free_entry_ptr(t_entry **entry);

t_list *mx_get_entries_in_directory(t_entry directory, t_find_entries_flags find_entries_flags);
t_list *mx_get_entries_in_directory_recursively(t_entry directory, t_find_entries_flags find_entries_flags);

void mx_print_entries_in_columns(t_list *entries_list, c_char column_delimiter, ushort terminal_width, bool print_newline_in_the_end, bool colorized, bool slash_after_dirs);
void mx_print_long_formatted_entries(t_list *entries_list, c_time_type time_type, bool print_total_number_of_512_byte_blocks, bool print_newline_in_the_end, c_long_format_flags long_format_flags);
void mx_print_entries_per_line(t_list *entries_list, bool colorized, bool print_newline_in_the_end, bool slash_after_dirs);

size_t mx_print_entry_name(t_entry *entry, bool colorized, bool slash_after_dirs);

void mx_print_long_formatted_entry(t_entry entry, size_t *column_sizes, c_time_type time_type, c_long_format_flags long_format_flags);

bool mx_sort_entries_by_name(void *a, void *b);
bool mx_sort_entries_by_size(void *a, void *b);
bool mx_sort_entries_by_last_modification(void *a, void *b);
bool mx_sort_entries_by_last_access(void *a, void *b);
bool mx_sort_entries_by_status_change(void *a, void *b);
bool mx_sort_entries_by_creation_time(void *a, void *b);
bool mx_reverse_entries(void *a, void *b);

void mx_free_files_dirs(t_files_dirs *files_dirs);
t_files_dirs mx_separate_entries(t_list *entries_list);

float mx_round_down(c_float number);
float mx_round_up(c_float number);
float mx_round(c_float number);

void mx_print_char_and_int_if( c_bool condition, c_char character, c_int integer);
void mx_print_char_and_int(c_char character, c_int integer);
void mx_print_char_and_string(c_char character, c_str string);
void mx_print_two_chars(c_char character1, c_char character2);
void mx_print_two_strings_if(c_bool condition, c_str string1, c_str string2);
void mx_print_two_strings(c_str string1, c_str string2);
void mx_printchar_if(c_bool condition, c_char character);
void mx_printnchar_if(c_bool condition, c_char character, c_size_t count);

ushort mx_get_terminal_width(void);
