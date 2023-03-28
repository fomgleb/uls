#include "../../../inc/utils.h"

void mx_free_files_dirs(t_files_dirs *files_dirs) {
    mx_clear_list(&files_dirs->files_list);
    mx_clear_list(&files_dirs->dirs_list);
}
