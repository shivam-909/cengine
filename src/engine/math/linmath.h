#ifndef LINMATH_H
#define LINMATH_H

#include "../types.h"

typedef struct v2_s
{
  f32 x, y;
} v2;

typedef struct v2i_s
{
  i32 x, y;
} v2i;

// Dot product of two vectors.
#define dot(v0, v1)                                                            \
  ({                                                                           \
    const v2 _v0 = (v0), _v1 = (v1);                                           \
    (_v0.x * _v1.x) + (_v0.y * _v1.y);                                         \
  })

// Length of a vector.
#define length(v)                                                              \
  ({                                                                           \
    const v2 _v = (v);                                                         \
    sqrtf(dot(_v, _v));                                                        \
  })

// Normalizes a vector.
#define normalize(u)                                                           \
  ({                                                                           \
    const v2 _u = (u);                                                         \
    const f32 l = length(_u);                                                  \
    (v2){_u.x / l, _u.y / l};                                                  \
  })

// Expands to the smaller vector.
#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a), _b = (b);                                          \
    _a < _b ? _a : _b;                                                         \
  })

// Expands to the larger vector.
#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a), _b = (b);                                          \
    _a > _b ? _a : _b;                                                         \
  })

// Returns the sign -1 or 1 of a number.
#define sign(a)                                                                \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    (__typeof__(a))(_a < 0 ? -1 : (_a > 0 ? 1 : 0));                           \
  })

#endif
