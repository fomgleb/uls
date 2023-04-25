#include "../inc/utils.h"

size_t mx_printstr_if(c_bool condition, c_str string) {
    if (condition) {
        return mx_printstr(string);
    }
    return 0;
}
