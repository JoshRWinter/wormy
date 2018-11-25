#ifndef WORMY_H
#define WORMY_H

#ifndef NDEBUG
#include <press.h>
#define logger(...) press::writeln(__VA_ARGS__)
#else
#define logger(...)
#endif

#include <win.h>
#include <Renderer.h>

#endif
