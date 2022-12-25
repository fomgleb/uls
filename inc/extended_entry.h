#pragma once

#include "entry.h"
#include "base_includes.h"

char *mx_get_permissions_str(mode_t file_mode, char *path_to_file);
unsigned int mx_get_number_of_links(t_entry entry);

