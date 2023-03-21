#pragma once

#include "../libmx/inc/libmx.h"
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#ifdef __APPLE__
#include <sys/acl.h>
#endif
#include <sys/xattr.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdbool.h>
