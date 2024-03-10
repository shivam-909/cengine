#include "SDL.h"
#include "engine/render/render.h"
#include "engine/state.h"
#include "engine/types.h"
#include "engine/view/view.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

  EngineState engine_state = {0};
  // Initialise SDL
  init_render_state(&engine_state.render_state);

  while (!engine_state.quit)
  {
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
      switch (ev.type)
      {
      case SDL_QUIT:
        engine_state.quit = true;
        break;
      }
    }

    const u8 *keystate = SDL_GetKeyboardState(NULL);
    processk(&engine_state.render_state, keystate);

    memset(engine_state.render_state.pixels, 0,
           sizeof(engine_state.render_state.pixels));
    render(&engine_state.render_state);

    SDL_UpdateTexture(engine_state.render_state.texture, NULL,
                      engine_state.render_state.pixels, SCREEN_WIDTH * 4);
    SDL_RenderCopyEx(engine_state.render_state.renderer,
                     engine_state.render_state.texture, NULL, NULL, 0.0, NULL,
                     SDL_FLIP_VERTICAL);
    SDL_RenderPresent(engine_state.render_state.renderer);
  }

  SDL_DestroyTexture(engine_state.render_state.texture);
  SDL_DestroyRenderer(engine_state.render_state.renderer);
  SDL_DestroyWindow(engine_state.render_state.window);
  free_render_state(&engine_state.render_state);
  return 0;
}
