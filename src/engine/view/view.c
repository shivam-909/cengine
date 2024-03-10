#include "view.h"
#include "../global.h"

#define ROTATION_SPEED ((f32)3.0f * 0.016f)
#define MOVEMENT_SPEED ((f32)3.0f * 0.016f)

void rotate(f32 rot)
{
  const v2 d = global.render_state.params.dir,
           p = global.render_state.params.plane;
  global.render_state.params.dir.x = d.x * cos(rot) - d.y * sin(rot);
  global.render_state.params.dir.y = d.x * sin(rot) + d.y * cos(rot);
  global.render_state.params.plane.x = p.x * cos(rot) - p.y * sin(rot);
  global.render_state.params.plane.y = p.x * sin(rot) + p.y * cos(rot);
}

void processk(const u8 *keystate)
{
  if (keystate[SDL_SCANCODE_LEFT])
  {
    rotate(+ROTATION_SPEED);
  }

  if (keystate[SDL_SCANCODE_RIGHT])
  {
    rotate(-ROTATION_SPEED);
  }

  if (keystate[SDL_SCANCODE_UP])
  {
    global.render_state.params.pos.x +=
        global.render_state.params.dir.x * MOVEMENT_SPEED;
    global.render_state.params.pos.y +=
        global.render_state.params.dir.y * MOVEMENT_SPEED;
  }

  if (keystate[SDL_SCANCODE_DOWN])
  {
    global.render_state.params.pos.x -=
        global.render_state.params.dir.x * MOVEMENT_SPEED;
    global.render_state.params.pos.y -=
        global.render_state.params.dir.y * MOVEMENT_SPEED;
  }
}
