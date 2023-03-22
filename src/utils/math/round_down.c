#include "../../../inc/utils.h"

float mx_round_down(c_float number) {
    float converted_number = (float)((long long)number);
    if (converted_number == number || number >= 0) {
        return converted_number;
    }
    return converted_number - 1;
}

