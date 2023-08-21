#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

struct point {
  int x;
  int y;
};

int _printf(const char *format, ...);

#endif /* MAIN_H */
