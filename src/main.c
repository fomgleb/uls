#include "../inc/base_includes.h"

char **get_all_names_in_directory(char *directory_name) {
    char **all_names = NULL;
    int all_names_len = 0;
    struct dirent *directory_content = NULL;
    DIR *directory = opendir(directory_name);

    if (directory == NULL) {
        return NULL;
    }
    
    directory_content = readdir(directory);
    while(directory_content != NULL) {
        all_names = mx_realloc(all_names, sizeof(char *) * ++all_names_len);
        all_names[all_names_len - 1] = mx_strdup(directory_content->d_name);
        directory_content = readdir(directory);
    }

    all_names = mx_realloc(all_names, sizeof(char *) * ++all_names_len);
    all_names[all_names_len - 1] = NULL;

    closedir(directory);
    
    return all_names;
}

int main(int argc, char **argv) {


    mx_printstr("BAZA:");
    mx_printint(32);
    mx_printstr("\n");
    
    errno = 0;
    char **all_names_in_current_directory = get_all_names_in_directory(".");
    printf("errno = %d\n", errno);  
    perror("shit gavno");
    printf("\nMambus: %s", (char *)strerror(errno));

    mx_print_strarr(all_names_in_current_directory, "  ");

    // for (int i = 0; all_names_in_current_directory[i] != NULL; i++) {
    //     free(all_names_in_current_directory[i]);
    // }
    free(all_names_in_current_directory);

    (void)argv;
    (void)argc;
    
    return 0;
}
