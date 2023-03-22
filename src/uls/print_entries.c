#include "../../inc/uls.h"

void mx_print_entries(t_list *entries_list, t_output_format output_format, t_print_entries_flags print_entries_flags) {
    switch (output_format) {
        case LONG_OUTPUT_FORMAT:
            mx_print_long_formatted_files_and_directories(entries_list, print_entries_flags & RECURSIVE_OUTPUT);
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

