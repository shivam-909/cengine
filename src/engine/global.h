//
// Created by Shivam Acharya on 02/02/2024.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include "render/render.h"

typedef struct global
{
  RenderState render_state;
  // Flag for program control.
  bool quit;
} Global;

extern Global global;

#endif // GLOBAL_H
