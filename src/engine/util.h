//
// Created by Shivam Acharya on 02/02/2024.
//

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define EXITWERR(...) fprintf(stderr, __VA_ARGS__); exit(1);

#define RETURNWERR(R, ...)                                                     \
  fprintf(stderr, __VA_ARGS);                                                  \
  return R

#define ASSERT(_e, ...)                                                        \
  if (!(_e))                                                                   \
  {                                                                            \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

#endif // UTIL_H
