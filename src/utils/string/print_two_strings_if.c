#include "../../../inc/utils.h"

void mx_print_two_strings_if(bool condition, char *string1, char *string2) {
    if (condition) {
        mx_printstr(string1);
        mx_printstr(string2);
    }
}

