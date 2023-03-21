#pragma once

#include "base_includes.h"
#include "entry.h"

typedef struct s_entry t_entry;

#define SECONDS_IN_HALF_YEAR 15768000

size_t *mx_calculate_long_format_column_sizes(t_list *entries);
