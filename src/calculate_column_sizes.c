#include "../inc/calculate_column_sizes.h"

static t_long_format_column_sizes create_long_format_column_sizes() {
    t_long_format_column_sizes long_format_column_sizes = {
        .number_of_links_size = 0,
        .owner_name_size = 0,
        .group_name_size = 0,
        .number_of_bytes_size = 0
    };
    return long_format_column_sizes;
}

t_long_format_column_sizes mx_calculate_long_format_column_sizes(t_list *entries) {
    t_long_format_column_sizes long_format_column_sizes = create_long_format_column_sizes();
    for (t_list *i = entries; i != NULL; i = i->next) {
        t_entry entry = *(t_entry *)i->data;

        size_t number_of_links_len = mx_get_digits_count(entry.stat.st_nlink);
        if (number_of_links_len > long_format_column_sizes.number_of_links_size) {
            long_format_column_sizes.number_of_links_size = number_of_links_len;
        }

        size_t owner_name_len = mx_strlen(getpwuid(entry.stat.st_uid)->pw_name);
        if (owner_name_len > long_format_column_sizes.owner_name_size) {
            long_format_column_sizes.owner_name_size = owner_name_len;
        }

        size_t group_name_len = mx_strlen(getgrgid(entry.stat.st_gid)->gr_name);
        if (group_name_len > long_format_column_sizes.group_name_size) {
            long_format_column_sizes.group_name_size = group_name_len;
        }

        size_t number_of_bytes_len = mx_get_digits_count(entry.stat.st_size);
        if (number_of_bytes_len > long_format_column_sizes.number_of_bytes_size) {
            long_format_column_sizes.number_of_bytes_size = number_of_bytes_len;
        }
    }
    return long_format_column_sizes;
}

