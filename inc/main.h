#pragma once

#include "base_includes.h"
#include "base_defines.h"
#include "args.h"
#include "entry.h"
#include "args_error.h"
#include "flags.h"
#include "extended_entry.h"
#include "printers.h"

typedef struct s_printable_extended_entry {
    char *file_mode;
    unsigned long int links_count;
    char *owner_name;
    char *group_name;
    long int bytes_count;
    
} t_printable_extended_entry;
