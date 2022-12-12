#pragma once

#include "../inc/base_includes.h"
#include "../inc/base_defines.h"
#include "../inc/args.h"
#include "../inc/entry.h"
#include "../inc/args_error.h"
#include "../inc/flags.h"

void mx_prepare_args(t_args *args, const char *existing_args);
t_list *mx_find_entries_list(t_args args);
void mx_print_directory_content_recursively(t_entry directory);
void mx_sort_entries_list_recursively(t_list *entries_list, t_args args);
void mx_free_main_variables(t_args args, t_list *entries_list);

