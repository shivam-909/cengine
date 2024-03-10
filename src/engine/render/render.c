//
// Created by Shivam Acharya on 02/02/2024.
//
//

#include "render.h"
#include "../map/map.h"
#include "../util.h"
#include "render_internal.h"
#include <math.h>
#include <stdio.h>

static void render_vertical_line(RenderState *render_state, int x, int y0,
                                 int y1, u32 color)
{
  for (int y = y0; y <= y1; y++)
  {
    render_state->pixels[(y * SCREEN_WIDTH) + x] = color;
  }
}

void render(RenderState *render_state)
{
  for (int x = 0; x < SCREEN_WIDTH; x++)
  {
    const f32 xcam = (2 * (x / (f32)(SCREEN_WIDTH))) - 1;

    const v2 dir = {
        render_state->params.dir.x + render_state->params.plane.x * xcam,
        render_state->params.dir.y + render_state->params.plane.y * xcam};

    v2 pos = render_state->params.pos;
    v2i ipos = {(int)pos.x, (int)pos.y};

    // The distance a ray needs to travel to intersect with a grid line, for
    // both x and y. Epsilon is used to avoid division by zero.
    const v2 delta_distance = {
        fabsf(dir.x) < EPSILON ? LARGE_VALUE : fabsf(1.0f / dir.x),
        fabsf(dir.y) < EPSILON ? LARGE_VALUE : fabsf(1.0f / dir.y),
    };

    // The distance a ray needs to trave from pos, to the first grid line, for
    // both x and y.
    v2 side_distance = {
        delta_distance.x *
            (dir.x < 0 ? (pos.x - ipos.x) : (ipos.x + 1 - pos.x)),
        delta_distance.y *
            (dir.y < 0 ? (pos.y - ipos.y) : (ipos.y + 1 - pos.y)),
    };

    // Tells us the direction of the ray, 1 or -1, which will indicate up/down
    // or left/right.
    const v2i step = {(int)sign(dir.x), (int)sign(dir.y)};

    RaycastHit hit = {0, 0, {0.0f, 0.0f}};

    while (!hit.val)
    {
      if (side_distance.x < side_distance.y)
      {
        side_distance.x += delta_distance.x;
        ipos.x += step.x;
        hit.side = 0;
      }
      else
      {
        side_distance.y += delta_distance.y;
        ipos.y += step.y;
        hit.side = 1;
      }

      ASSERT(ipos.x >= 0 && ipos.x < MAP_SIZE && ipos.y >= 0 &&
                 ipos.y < MAP_SIZE,
             "out of bounds");

      // Populate with the value of the map at the current position. Non-zero
      // values are walls.
      hit.val = MAPDATA[ipos.y * MAP_SIZE + ipos.x];
    }

    u32 color;
    switch (hit.val)
    {
    case 1:
      color = 0xFF0000FF;
      break;
    case 2:
      color = 0xFF00FF00;
      break;
    case 3:
      color = 0xFFFF0000;
      break;
    case 4:
      color = 0xFFFF00FF;
      break;
    }

    // Shading hack. Wall is lighter or darker depending on what grid line its
    // perpendicular to.
    if (hit.side == 1)
    {
      const u32 br = ((color & 0xFF00FF) * 0xC0) >> 8,
                g = ((color & 0x00FF00) * 0xC0) >> 8;

      color = 0xFF000000 | (br & 0xFF00FF) | (g & 0x00FF00);
    }

    hit.pos = (v2){pos.x + side_distance.x, pos.y + side_distance.y};

    const f32 dperp = hit.side == 0 ? (side_distance.x - delta_distance.x)
                                    : (side_distance.y - delta_distance.y);

    // Perspective division, and screen mapping.
    const int h = (int)(SCREEN_HEIGHT / dperp),
              y0 = max((SCREEN_HEIGHT / 2) - (h / 2), 0),
              y1 = min((SCREEN_HEIGHT / 2) + (h / 2), SCREEN_HEIGHT - 1);

    render_vertical_line(render_state, x, 0, y0, 0xFF202020);
    render_vertical_line(render_state, x, y0, y1, color);
    render_vertical_line(render_state, x, y1, SCREEN_HEIGHT - 1, 0xFF505050);
  }
}
