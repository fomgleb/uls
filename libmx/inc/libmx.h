#pragma once

#include <unistd.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#ifdef __APPLE__
#include <malloc/malloc.h>
#endif
#ifdef __linux__
#include <malloc.h>
#define malloc_size malloc_usable_size
#endif

// List
typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;
void mx_clear_list(t_list **list);
t_list *mx_create_node(void *data);
t_list *mx_get_by_index(t_list *head, int index);
int mx_list_size(t_list *list);
void mx_reverse_list(t_list *head);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
void mx_pop_index(t_list **list, int index);
void mx_pop_node(t_list **head, t_list *node);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);

//Memory
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memset(void *b, int c, size_t len);
void *mx_realloc(void *ptr, size_t size);

// Printers
void mx_print_strarr(char **arr, const char *delim);
void mx_printchar(char c);
void mx_printerr(const char *s);
void mx_printerrch(const char c);
void mx_printerrn(const char *s, int n);
void mx_printint(int n);
void mx_printnchar(char character, size_t count);
void mx_printnstr(const char *string, size_t count);
size_t mx_printstr(const char *const string);

// String
int mx_atoi(const char *str);
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char с);
void mx_del_strarr(char ***arr);
char *mx_file_to_str(const char *file);
void mx_free_str_arr(char ***str_arr);
int mx_get_char_index(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);
int mx_iterative_search(char **strings, int count, char *searching);
char *mx_itoa(int number);
char *mx_nbr_to_hex(unsigned long nbr);
bool mx_num_in_str_is_positive(char *str);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
void mx_reverse_array(char **strarr);
int mx_strarr_len(char **strarr);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strchr_last(const char *s, int c);
char *mx_strchr(const char *s, int c);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
void mx_strdel(char **str);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
size_t mx_strlen(const char *const string);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strndup(const char *s1, size_t n);
char *mx_strnew(const int size);
char **mx_strsplit(char const *s, char c);

int mx_get_digits_count(int num);
bool mx_isspace(char c);
bool mx_isdigit(int c);
bool mx_isalpha(int c);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
unsigned long mx_hex_to_nbr(const char *hex);
void mx_foreach(int *arr, int size, void (*f)(int));
void mx_swap_char(char *s1, char *s2);
