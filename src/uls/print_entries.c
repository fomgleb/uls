#include "../../inc/uls.h"

static t_flags *Flags = NULL;
static t_output_format OutputFormat;
static char ColumnDelimiter = 0;
static ushort TerminalWidth = 0;
static t_time_type TimeType;
static bool PrintTotalNumberOf512ByteBlocks = false;

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

static t_output_format get_output_format(t_flags *flags) {
    bool output_is_to_terminal = isatty(STDOUT_FILENO);
    int priority_flag = MAX6(flags->C, flags->one, flags->l, flags->o, flags->g, flags->m);
    priority_flag = priority_flag == 0 ? -1 : priority_flag;
    if (output_is_to_terminal) {
        if (priority_flag == (int)flags->one) {
            return ONE_ENTRY_PER_LINE_OUTPUT_FORMAT;
        } else if (priority_flag == (int)flags->l || priority_flag == (int)flags->o || priority_flag == (int)flags->g) {
            return LONG_OUTPUT_FORMAT;
        } else if (priority_flag == (int)flags->m) {
            return SEPARATED_BY_COMMAS_OUTPUT_FORMAT;
        } else {
            return MULTI_COLUMN_OUTPUT_FORMAT;
        }
    } else {
        if (priority_flag == (int)flags->C) {
            return MULTI_COLUMN_OUTPUT_FORMAT;
        } else if (priority_flag == (int)flags->l || priority_flag == (int)flags->o || priority_flag == (int)flags->g) {
            return LONG_OUTPUT_FORMAT;
        } else if (priority_flag == (int)flags->m) {
            return SEPARATED_BY_COMMAS_OUTPUT_FORMAT;
        } else {
            return ONE_ENTRY_PER_LINE_OUTPUT_FORMAT;
        }
    }
}

static t_long_format_flags flags_to_long_format_flags(t_flags *flags) {
    t_long_format_flags long_format_flags = 0;
    long_format_flags |= (flags->at ? DISPLAY_EXTENDED_ATTRIBUTES : 0) |
                         (flags->T ? FULL_TIME_INFO : 0) |
                         (flags->h ? HUMAN_READABLE_SIZE : 0) |
                         (flags->o ? HIDE_GROUP_NAME : 0) |
                         (flags->g ? HIDE_OWNER_NAME : 0) |
                         (flags->e ? PRINT_ACCESS_CONTROL_LIST : 0);
    return long_format_flags;
}

static t_entry_printing_flags flags_to_entry_printing_flags(t_flags *flags) {
    t_entry_printing_flags entry_printing_flags = 0;
    entry_printing_flags |= (flags->G && isatty(STDOUT_FILENO) ? IS_COLORIZED : 0) |
                            (flags->p ? PRINT_SLASH_AFTER_DIRECTORIES : 0);
    return entry_printing_flags;
}

static void print_entries(t_list *entries_list, bool print_newline_in_the_end) {
    switch (OutputFormat) {
        case ONE_ENTRY_PER_LINE_OUTPUT_FORMAT:
            mx_print_entries_per_line(entries_list, flags_to_entry_printing_flags(Flags));
        break;
        case MULTI_COLUMN_OUTPUT_FORMAT:
            mx_print_entries_in_columns(entries_list, ColumnDelimiter, TerminalWidth, flags_to_entry_printing_flags(Flags));
        break;
        case LONG_OUTPUT_FORMAT:
            mx_print_long_formatted_entries(entries_list, TimeType, PrintTotalNumberOf512ByteBlocks, flags_to_long_format_flags(Flags), flags_to_entry_printing_flags(Flags));
        break;
        case SEPARATED_BY_COMMAS_OUTPUT_FORMAT:
            mx_print_entries_separated_by_commas(entries_list, TerminalWidth, flags_to_entry_printing_flags(Flags));
        break;
    }
    mx_printchar_if(print_newline_in_the_end && entries_list, '\n');
}

static void print_directory_content_recursively(t_entry *directory, bool print_dir_name, bool print_newline_in_the_beginning) {
    mx_printchar_if(print_newline_in_the_beginning, '\n');
    mx_print_two_strings_if(print_dir_name, directory->relative_path, ":\n");
    PrintTotalNumberOf512ByteBlocks = true;
    print_entries(directory->entries_list, false);

    t_files_dirs files_dirs = mx_separate_entries(directory->entries_list, false);
    for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
        t_entry *i_directory = (t_entry *)i->data;
        if (mx_strcmp(i_directory->dirent->d_name, ".") != 0 && mx_strcmp(i_directory->dirent->d_name, "..") != 0) {
            print_directory_content_recursively((t_entry *)i->data, true, true);
        }
    }
    mx_free_files_dirs(&files_dirs);
}

static void set_global_variables(t_flags *flags) {
    Flags = flags;
    OutputFormat = get_output_format(flags);
    switch (OutputFormat) {
        case ONE_ENTRY_PER_LINE_OUTPUT_FORMAT:
        break;
        case MULTI_COLUMN_OUTPUT_FORMAT:
            TerminalWidth = mx_get_terminal_width();
            ColumnDelimiter = flags->G && isatty(STDOUT_FILENO) ? ' ' : '\t';
        break;
        case LONG_OUTPUT_FORMAT:
            TimeType = get_time_type(flags);
        break;
        case SEPARATED_BY_COMMAS_OUTPUT_FORMAT:
            TerminalWidth = mx_get_terminal_width();
        break;
    }
}

void mx_print_files_and_directories(t_list *entries_list, t_flags *flags, c_size_t invalid_paths_to_entries_count) {
    set_global_variables(flags);
    if (flags->d) {
        print_entries(entries_list, false);
    } else {
        t_files_dirs files_dirs = mx_separate_entries(entries_list, !flags->l && !flags->g && !flags->o);
        PrintTotalNumberOf512ByteBlocks = files_dirs.dirs_list != NULL;
        print_entries(files_dirs.files_list, files_dirs.dirs_list != NULL);
        if (flags->R) {
            for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
                t_entry *directory = (t_entry *)i->data;
                print_directory_content_recursively(directory, files_dirs.total_entries_count + invalid_paths_to_entries_count > 1, false);
                mx_printchar_if(i->next != NULL, '\n');
            }
        } else {
            for (t_list *i = files_dirs.dirs_list; i != NULL; i = i->next) {
                t_entry *directory = (t_entry *)i->data;
                mx_print_two_strings_if(files_dirs.total_entries_count + invalid_paths_to_entries_count > 1, directory->relative_path, ":\n");
                PrintTotalNumberOf512ByteBlocks = true;
                print_entries(directory->entries_list, i->next != NULL);
            }
        }
        mx_free_files_dirs(&files_dirs);
    }
}
