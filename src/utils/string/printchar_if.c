#include "../../../inc/utils.h"

void mx_printchar_if(bool condition, char character) {
    if (condition) {
        mx_printchar(character);
    }
}

