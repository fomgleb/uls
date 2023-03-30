#include "../../../inc/utils.h"

float mx_round(c_float number) {
    if (number < 0) {
        return (float)((int)(number - 0.5));
    } else {
        return (float)((int)(number + 0.5));
    }
}
