#include "../../../inc/utils.h"

void mx_print_two_strings_if(c_bool condition, c_str string1, c_str string2) {
    if (condition) {
        mx_print_two_strings(string1, string2);
    }
}

