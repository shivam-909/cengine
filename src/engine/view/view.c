#include "view.h"

#define ROTATION_SPEED ((f32)3.0f * 0.016f)
#define MOVEMENT_SPEED ((f32)3.0f * 0.016f)

void rotate(RenderState *render_state, f32 rot)
{
  const v2 d = render_state->params.dir, p = render_state->params.plane;
  render_state->params.dir.x = d.x * cos(rot) - d.y * sin(rot);
  render_state->params.dir.y = d.x * sin(rot) + d.y * cos(rot);
  render_state->params.plane.x = p.x * cos(rot) - p.y * sin(rot);
  render_state->params.plane.y = p.x * sin(rot) + p.y * cos(rot);
}

void processk(RenderState *render_state, const u8 *keystate)
{
  if (keystate[SDL_SCANCODE_LEFT])
  {
    rotate(render_state, +ROTATION_SPEED);
  }

  if (keystate[SDL_SCANCODE_RIGHT])
  {
    rotate(render_state, -ROTATION_SPEED);
  }

  if (keystate[SDL_SCANCODE_UP])
  {
    render_state->params.pos.x += render_state->params.dir.x * MOVEMENT_SPEED;
    render_state->params.pos.y += render_state->params.dir.y * MOVEMENT_SPEED;
  }

  if (keystate[SDL_SCANCODE_DOWN])
  {
    render_state->params.pos.x -= render_state->params.dir.x * MOVEMENT_SPEED;
    render_state->params.pos.y -= render_state->params.dir.y * MOVEMENT_SPEED;
  }
}
