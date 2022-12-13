#pragma once

#include "base_includes.h"
#include "base_defines.h"
#include "args.h"
#include "entry.h"
#include "args_error.h"
#include "flags.h"
#include "printable_entry.h"

void mx_prepare_args(t_args *args, const char *existing_args);
t_list *mx_find_entries_list(t_list *input_entry_names, t_flags flags);
// void mx_print_directory_content_recursively(t_entry directory);
void mx_sort_entries_list_recursively(t_list *entries_list, t_flags flags);
void mx_print_entries_list(t_list *entries_list, t_flags flags);
void mx_free_main_variables(t_args args, t_list *entries_list);

