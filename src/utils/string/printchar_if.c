#include "../../../inc/utils.h"

void mx_printchar_if(c_bool condition, c_char character) {
    if (condition) {
        mx_printchar(character);
    }
}

