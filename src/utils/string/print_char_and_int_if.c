#include "../../../inc/utils.h"

void mx_print_char_and_int_if(c_bool condition, c_char character, c_int integer) {
    if (condition) {
        mx_print_char_and_int(character, integer);
    }
}
