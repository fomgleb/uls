#include "../../inc/printers.h"

static void print_entry_permissions_with_indent(t_entry *entry) {
    char *permissions_str = mx_get_permissions_str(entry->stat.st_mode, entry->relative_path);
    mx_printstr(permissions_str);
    free(permissions_str);
    mx_printchar(' ');
}

static void print_number_of_entry_links_with_indent(t_entry *entry, size_t column_size) {
    int indent = column_size - mx_get_digits_count(entry->stat.st_nlink);
    mx_printnchar(' ', indent);
    mx_printint(entry->stat.st_nlink);
    mx_printchar(' ');
}

static void print_owner_name_with_indent(t_entry *entry, size_t column_size) {
    mx_printstr(getpwuid(entry->stat.st_uid)->pw_name);
    mx_printnchar(' ', column_size - mx_strlen(getpwuid(entry->stat.st_uid)->pw_name));
    mx_printnchar(' ', 2);
}

static void print_group_name_with_indent(t_entry *entry, size_t column_size) {
    mx_printstr(getgrgid(entry->stat.st_gid)->gr_name);
    mx_printnchar(' ', column_size - mx_strlen(getgrgid(entry->stat.st_gid)->gr_name));
    mx_printnchar(' ', 2);
}

static void print_number_of_entry_bytes(t_entry *entry, size_t column_size) {
    mx_printnchar(' ', column_size - mx_get_digits_count(entry->stat.st_size));
    mx_printint(entry->stat.st_size);
    mx_printchar(' ');
}

static void print_month_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 4, 3);
    mx_printchar(' ');
}

static void print_month_day_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 8, 2);
    mx_printchar(' ');
}

static void print_hours_and_minutes_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 11, 5);
    mx_printchar(' ');
}

static void print_year_with_indent(char *human_readable_time) {
    mx_printnstr(human_readable_time + 19, 5);
    mx_printchar(' ');
}

static void print_link_content(t_entry entry) {
    char link_content[1024];
    ssize_t link_content_len = readlink(entry.relative_path, link_content, 1024);
    mx_printnstr(link_content, link_content_len);
}

static time_t calculate_difference_between_times(time_t time1, time_t time2) {
    if (time1 > time2) {
        return time1 - time2;
    } else {
        return time2 - time1;
    }
}

t_long_format_column_sizes create_long_format_column_sizes() {
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

void mx_print_long_formatted_entry(t_entry entry, t_long_format_column_sizes column_sizes) {
    print_entry_permissions_with_indent(&entry);
    print_number_of_entry_links_with_indent(&entry, column_sizes.number_of_links_size);
    print_owner_name_with_indent(&entry, column_sizes.owner_name_size);
    print_group_name_with_indent(&entry, column_sizes.group_name_size);
    print_number_of_entry_bytes(&entry, column_sizes.number_of_bytes_size);
    char *human_readable_time = ctime(&entry.stat.st_mtime);
    print_month_with_indent(human_readable_time);
    print_month_day_with_indent(human_readable_time);
    if (calculate_difference_between_times(entry.stat.st_mtime, time(NULL)) > SECONDS_IN_HALF_YEAR) {
        print_year_with_indent(human_readable_time);
    } else {
        print_hours_and_minutes_with_indent(human_readable_time);
    }
    mx_printstr(entry.dirent != NULL ? entry.dirent->d_name : entry.relative_path);
    if (S_ISLNK(entry.stat.st_mode)) {
        mx_printstr(" -> ");
        print_link_content(entry);
    }
    mx_printchar('\n');
}

