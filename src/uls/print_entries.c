#include "../../inc/uls.h"

static c_time_type get_time_type(c_flags_ptr flags) {
    t_time_type time_type = TIME_OF_LAST_DATA_MODIFICATION;
    if (flags->c) {
        time_type = TIME_OF_LAST_FILE_STATUS_CHANGE;
    } else if (flags->u) {
        time_type = TIME_OF_LAST_ACCESS;
    } else if (flags->U) {
        time_type = TIME_OF_FILE_CREATION;
    }
    return time_type;
}

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags, c_flags_ptr flags_ptr) {
    switch (output_format) {
        case LONG_OUTPUT_FORMAT:
            mx_print_long_formatted_files_and_directories(entries_list, get_time_type(flags_ptr), print_entries_flags & RECURSIVE_OUTPUT);
        break;
        case MULTI_COLUMN_OUTPUT_FORMAT:
            mx_print_files_and_directories_in_columns(entries_list, print_entries_flags & COLORIZED_OUTPUT,
                                                                    print_entries_flags & RECURSIVE_OUTPUT);
        break;
        case ONE_ENTRY_PER_LINE_OUTPUT_FORMAT:
            mx_print_files_and_directories_per_line(entries_list, print_entries_flags & RECURSIVE_OUTPUT);
        break;
    }
}

