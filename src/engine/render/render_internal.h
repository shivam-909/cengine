//
// Created by Shivam Acharya on 02/02/2024.
//

#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include "../math/linmath.h"
#include "render.h"
#include <stdbool.h>

typedef struct
{
  int val, side;
  v2 pos;
} RaycastHit;

static void render_vertical_line(RenderState *render_state, int x, int y0, int y1, u32 color);

#endif // RENDER_INTERNAL_H
