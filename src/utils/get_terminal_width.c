#include "../../inc/utils.h"

ushort mx_get_terminal_width() {
    struct winsize winsize;
    ioctl(0, TIOCGWINSZ, &winsize);
    return winsize.ws_col;
}

