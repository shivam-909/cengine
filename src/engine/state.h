//
// Created by Shivam Acharya on 02/02/2024.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include "render/render.h"

typedef struct engine_state
{
  RenderState render_state;
  // Flag for program control.
  bool quit;
} EngineState;

#endif // GLOBAL_H
