#ifndef VIEW_H
#define VIEW_H

#include "../types.h"
#include "../render/render.h"

void rotate(RenderState *render_state, f32 rot);

void processk(RenderState *render_state, const u8 *ks);

#endif // !VIEW.H
