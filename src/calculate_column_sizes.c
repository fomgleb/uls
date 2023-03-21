#include "../inc/uls.h"

static size_t *create_empty_size_t_array(size_t size) {
    size_t *array = malloc(size * sizeof(size_t));
    for (size_t i = 0; i < size; i++) {
        array[i] = 0;
    }
    return array;
}

size_t *mx_calculate_long_format_column_sizes(t_list *entries) {
    size_t *column_sizes = create_empty_size_t_array(4);
    for (t_list *i = entries; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;

        size_t number_of_links_len = mx_get_digits_count(entry.stat.st_nlink);
        if (number_of_links_len > column_sizes[0]) {
            column_sizes[0] = number_of_links_len;
        }

        size_t owner_name_len = mx_strlen(getpwuid(entry.stat.st_uid)->pw_name);
        if (owner_name_len > column_sizes[1]) {
            column_sizes[1] = owner_name_len;
        }

        size_t group_name_len = mx_strlen(getgrgid(entry.stat.st_gid)->gr_name);
        if (group_name_len > column_sizes[2]) {
            column_sizes[2] = group_name_len;
        }

        size_t number_of_bytes_len = mx_get_digits_count(entry.stat.st_size);
        if (number_of_bytes_len > column_sizes[3]) {
            column_sizes[3] = number_of_bytes_len;
        }
    }
    return column_sizes;
}

