#include "../../inc/printers.h"

static void print_entry_permissions(t_entry entry) {
    char *permissions_str = mx_get_permissions_str(entry.stat.st_mode, entry.relative_path);
    mx_printstr(permissions_str);
    free(permissions_str);
}

static void print_number_of_entry_links(t_entry entry) {
    mx_printint(entry.stat.st_nlink);
}

static void print_owner_name(t_entry entry) {
    mx_printstr(getpwuid(entry.stat.st_uid)->pw_name);
}

static void print_group_name(t_entry entry) {
    mx_printstr(getgrgid(entry.stat.st_gid)->gr_name);
}

static void print_number_of_entry_bytes(t_entry entry) {
    mx_printint(entry.stat.st_size);
}

static void print_month(char *human_readable_time) {
    mx_printnstr(human_readable_time + 4, 3);
}

static void print_month_day(char *human_readable_time) {
    mx_printnstr(human_readable_time + 8, 2);
}

static void print_hours_and_minutes(char *human_readable_time) {
    mx_printnstr(human_readable_time + 11, 5);
}

static void print_year(char *human_readable_time) {
    mx_printnstr(human_readable_time + 20, 4);
}

static time_t calculate_difference_between_times(time_t time1, time_t time2) {
    if (time1 > time2) {
        return time1 - time2;
    } else {
        return time2 - time1;
    }
}

void mx_print_long_formatted_entry(t_entry entry) {
    print_entry_permissions(entry);
    mx_printchar(' ');
    print_number_of_entry_links(entry);
    mx_printchar(' ');
    print_owner_name(entry);
    mx_printchar(' ');
    print_group_name(entry);
    mx_printchar(' ');
    print_number_of_entry_bytes(entry);
    mx_printchar(' ');
    char *human_readable_time = ctime(&entry.stat.st_mtime);
    print_month(human_readable_time);
    mx_printchar(' ');
    print_month_day(human_readable_time);
    mx_printchar(' ');
    if (calculate_difference_between_times(entry.stat.st_mtime, time(NULL)) > SECONDS_IN_HALF_YEAR) {
        print_year(human_readable_time);
    } else {
        print_hours_and_minutes(human_readable_time);
    }
    mx_printchar(' ');
    mx_printstr(entry.relative_path);
    mx_printchar('\n');
}

