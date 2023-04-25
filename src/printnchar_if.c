#include "../inc/utils.h"

void mx_printnchar_if(c_bool condition, c_char character, c_size_t count) {
    if (condition) {
        mx_printnchar(character, count);
    }
}
