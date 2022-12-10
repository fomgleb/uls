#pragma once

#include <unistd.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#endif

#ifdef __linux__
#include <malloc.h>
#define malloc_size malloc_usable_size
#endif

#include <stdio.h>

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

// My
int mx_get_digits_count(int num);
char *mx_strchr(const char *s, int c);
int mx_strncmp(const char *s1, const char *s2, int n);
bool mx_isspace(char c);
int mx_atoi(const char *str);
int mx_strarr_len(char **strarr);
bool mx_isdigit(int c);
int mx_iterative_search(char **strings, int count, char *searching);
void mx_printerr(const char *s);
void mx_pop_index(t_list **list, int index);
void mx_clear_list(t_list **list);
t_list *mx_get_by_index(t_list *head, int index);
bool mx_num_in_str_is_positive(char *str);
void mx_free_str_arr(char ***str_arr);
bool mx_isalpha(int c);
void mx_printerrn(const char *s, int n);
void mx_pop_node(t_list **head, t_list *node);
void mx_printerrch(const char c);

// Need
void mx_printchar(char c);
void mx_print_unicode(wchar_t c);
// Description: Test with a random input
// user output vs test output
// 1c1
// < �
// \ No newline at end of file
// ---
// > b'\xf6\xbe\xab\x88'
// \ No newline at end of file
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
char *mx_nbr_to_hex(unsigned long nbr);
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_itoa(int number);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
// Description: test with random strings
// user output vs test output
// 2c2
// < found = 1, count = 3
// ---
// > found = 1, count = 2 
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);
// Description: Test with a random input
// user output vs test output
// 1c1
// < swaps = 4
// ---
// > swaps = 6
// 5d4
// < |cuTSWt6lnkeHKKr|
// 6a6
// > |cuTSWt6lnkeHKKr|
// 9,10d8
// < |C5k4aykmjHpr9ZP7ebzW|
// < |rZK79Wt22ZDqIRHkMQ   D|
// 11a10,11
// > |rZK79Wt22ZDqIRHkMQ   D|
// > |C5k4aykmjHpr9ZP7ebzW|

// Description: Test with a random input
// user output vs test output
// 1c1
// < swaps = 12
// ---
// > swaps = 14
// 8a9,10
// > |h2yZ2SqjVtv|
// > |gO3p9ZLxQCJ0|
// 11d12
// < |rGxpyIOgx2rl1|
// 13,15c14
// < |MAFw6MltJmYpkDB|
// < |gO3p9ZLxQCJ0|
// < |h2yZ2SqjVtv|
// ---
// > |rGxpyIOgx2rl1|
// 18a18
// > |MAFw6MltJmYpkDB|

// Description: Test with a random input
// user output vs test output
// 1c1
// < swaps = 54
// ---
// > swaps = 59
// 11d10
// < |FI GklOsc4|
// 14,16c13,15
// < |7d1aU3cYtc |
// < |4QejRPAHvFW|
// < |B34cxKPHymE|
// ---
// > |FI GklOsc4|
// > |y73  p59osf|
// > |BJ7GUEYE6Gy|
// 17a17
// > |B34cxKPHymE|
// 18a19
// > |7d1aU3cYtc |
// 20,21c21
// < |8i IZnU y8qL|
// < |uVh6OF109    81|
// ---
// > |4QejRPAHvFW|
// 23d22
// < |y73  p59osf|
// 24a24
// > |8i IZnU y8qL|
// 27a28,29
// > |uVh6OF109    81|
// > |dppo3UzdPP6ar|
// 31d32
// < |dppo3UzdPP6ar|
// 33d33
// < |ebls6z7LlJymAK|
// 34a35,37
// > |ebls6z7LlJymAK|
// > |Qn0D
// > ECjwW3M7cB|
// 38,41d40
// < |Qn0D
// < ECjwW3M7cB|
// < |BJ7GUEYE6Gy|
// < |6Tz4DIccJY   SMPk|
// 42a42
// > |6Tz4DIccJY   SMPk|
// 44,45d43
// < |VEMpRkJdNhCyHEPQ|
// < |NnP1LEJmH    OsFZS4|
// 46a45
// > |VEMpRkJdNhCyHEPQ|
// 49a49
// > |NnP1LEJmH    OsFZS4|
// 54,55c54
// < |ssz4l
// < E8D9AKwb8Ff|
// ---
// > |j5FZ0xzMJ7fkp57lq|
// 57a57,61
// > |uOBca        SpHu3
// > z6xK6|
// > |vFvHjyrrOBbTVQ2J4|
// > |ssz4l
// > E8D9AKwb8Ff|
// 61,66d64
// < |vFvHjyrrOBbTVQ2J4|
// < |j5FZ0xzMJ7fkp57lq|
// < |uOBca        SpHu3
// < z6xK6|
// < |VZxOap02dzyt8uwjxc|
// < |TrnFQAogThnkkx       dM5|
// 68c66
// < |TTOfV90Ro0xSJLxPPa|
// ---
// > |TrnFQAogThnkkx       dM5|
// 70a69
// > |VZxOap02dzyt8uwjxc|
// 71a71
// > |TTOfV90Ro0xSJLxPPa|
// 76a77
// > |Au6 9DMo9PlPU4Ydw5F|
// 79,81d79
// < |Au6 9DMo9PlPU4Ydw5F|
// < |qRby zEFYmRxCs
// < JC4Xp|
// 83a82,84
// > |ZU6nuQY5ulC3cJ7lBjGW|
// > |qRby zEFYmRxCs
// > JC4Xp|
// 86d86
// < |ZU6nuQY5ulC3cJ7lBjGW|

int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
// Description: Test with a random input
// user output vs test output
// 1c1
// < BdatKLxwCtlI75FsCUMcJcXxCSf9jgRQu8QmAzO9jDUXB3cxARruvr
// ---
// > BdatKLxwCtlI75FsCUMcJcXxCSf9jgRuQ8QmAzO9jDUXB3cxARruvr
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *str);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
// Description: Test with no input
// user output vs test output
// 1d0
// < (null)
// \ No newline at end of file

// Description: Test with a random input
// user output vs test output
// 1d0
// < H3IMoLe       hE
// \ No newline at end of file
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char с);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
// Description: Test with a random input
// user output vs test output
// 1,2c1,2
// < (null)
// < size of pointer: 0
// ---
// >
// > size of pointer: 16
char *mx_del_extra_spaces(const char *str);
// Description: Test with random input
// user output vs test output
// 1c1
// <  YaSKfwfBN3S7c06N9oyE4Namr1Y 95tLH6B
// ---
// > YaSKfwfBN3S7c06N9oyE4Namr1Y 95tLH6B

// Description: Test with random input
// user output vs test output
// 2c2
// < size of pointer: 64
// ---
// > size of pointer: 48

// Description: Test with random input
// user output vs test output
// 1,2c1,2
// < (null)
// < size of pointer: 0
// ---
// >
// > size of pointer: 16
char **mx_strsplit(char const *s, char c);
char *mx_strjoin(char const *s1, char const *s2);
char *mx_file_to_str(const char *file);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd); // In progress

void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
// Description: Test with a random input
// user output vs test output
// 1c1
// < l0 hbXqxOePGi4ZZ      YuWGdim
// \ No newline at end of file
// ---
// > (null)
// \ No newline at end of file
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));

