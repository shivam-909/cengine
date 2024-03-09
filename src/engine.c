#include "SDL.h"
#include "engine/global.h"
#include "engine/render/render.h"
#include "engine/types.h"
#include "engine/view/view.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

  // Initialise SDL
  init_render_state();

  while (!global.quit)
  {
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
      switch (ev.type)
      {
      case SDL_QUIT:
        global.quit = true;
        break;
      }
    }

    const u8 *keystate = SDL_GetKeyboardState(NULL);
    processk(keystate);

    memset(global.render_state.pixels, 0, sizeof(global.render_state.pixels));
    render();

    SDL_UpdateTexture(global.render_state.texture, NULL,
                      global.render_state.pixels, SCREEN_WIDTH * 4);
    SDL_RenderCopyEx(global.render_state.renderer, global.render_state.texture,
                     NULL, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(global.render_state.renderer);
  }

  SDL_DestroyTexture(global.render_state.texture);
  SDL_DestroyRenderer(global.render_state.renderer);
  SDL_DestroyWindow(global.render_state.window);
  free_render_state(&global.render_state);
  return 0;
}
