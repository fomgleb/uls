#include "../inc/utils.h"

ushort mx_get_terminal_width(void) {
    struct winsize winsize;
    ioctl(0, TIOCGWINSZ, &winsize);
    return winsize.ws_col;
}
