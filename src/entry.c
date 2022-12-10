#include "../inc/entry.h"

t_entry mx_create_entry(char *relative_path) {
    t_entry entry;
    entry.relative_path = mx_strdup(relative_path);
    stat(relative_path, &entry.stat);
    entry.entries_list = NULL;
    return entry;
}

t_entry *mx_create_entry_ptr(char *relative_path) {
    t_entry *entry = malloc(sizeof(t_entry));
    *entry = mx_create_entry(relative_path);
    return entry;
}

void mx_free_entry(t_entry entry) {
    free(entry.relative_path);
    for (t_list *node = entry.entries_list; node != NULL; node = node->next) {
        mx_free_entry(*(t_entry *)node->data);
        free(node->data);
    }
    mx_clear_list(&entry.entries_list);
}

void mx_free_entry_ptr(t_entry **entry) {
    mx_free_entry(**entry);
    free(*entry);
    *entry = NULL;
}

t_list *mx_get_entries_in_directory(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory) {
    t_list *read_entries_list = NULL;
    DIR *dirstream = opendir(directory.relative_path);

    for (struct dirent *i = readdir(dirstream); i != NULL; i = readdir(dirstream)) {
        if (!include_entries_stating_with_dot && i->d_name[0] == '.') {
            continue;
        }
        if (ignore_current_and_father_directory && (mx_strcmp(i->d_name, ".") == 0 || mx_strcmp(i->d_name, "..") == 0)) {
            continue;
        }
        char *new_entry_path = mx_strnew(mx_strlen(directory.relative_path) + mx_strlen("/") + mx_strlen(i->d_name));
        mx_strcat(mx_strcat(mx_strcat(new_entry_path, directory.relative_path), "/"), i->d_name);
        t_entry *new_entry = mx_create_entry_ptr(new_entry_path);
        free(new_entry_path);
        new_entry->dirent = *i;
        mx_push_front(&read_entries_list, new_entry);
    }
    
    closedir(dirstream);
    
    return read_entries_list;
}

t_list *mx_get_entries_in_directory_recursively(t_entry directory, bool include_entries_stating_with_dot, bool ignore_current_and_father_directory) {
    t_list *read_entries_list = mx_get_entries_in_directory(directory, include_entries_stating_with_dot, ignore_current_and_father_directory);
    for (t_list *i = read_entries_list; i != NULL; i = i->next) {
        t_entry *entry = (t_entry *)i->data;
        if (S_ISDIR(entry->stat.st_mode) && mx_strcmp(entry->dirent.d_name, ".") != 0 && mx_strcmp(entry->dirent.d_name, "..") != 0) {
            entry->entries_list = mx_get_entries_in_directory_recursively(*entry, include_entries_stating_with_dot, ignore_current_and_father_directory);
        }
    }
    return read_entries_list;
}

