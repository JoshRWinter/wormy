#ifndef WORMY_H
#define WORMY_H

#include <win.h>

#ifndef NDEBUG
#include <press.h>
#define logger(...) press::writeln(__VA_ARGS__)
#else
#define logger(...)
#endif

#endif
