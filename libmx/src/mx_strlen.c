#include "../inc/libmx.h"

size_t mx_strlen(const char *const string) {
    if (string == NULL) {
        return 0;
    }
    size_t length = 0;
    for ( ; string[length] != '\0'; length++) { }
    return length;
}
