#pragma once

#include "base_includes.h"
#include "entry.h"

typedef struct s_entry t_entry;

#define SECONDS_IN_HALF_YEAR 15768000

typedef struct s_long_format_column_sizes {
    size_t number_of_links_size;
    size_t owner_name_size;
    size_t group_name_size;
    size_t number_of_bytes_size;
} t_long_format_column_sizes;

t_long_format_column_sizes mx_calculate_long_format_column_sizes(t_list *entries);
