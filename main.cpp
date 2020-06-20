
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <thread>

struct context
{
    SDL_Renderer *renderer;
    int iteration;
    SDL_Texture *texture;
};

void loop(void *arg)
{
    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, ctx->texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    ctx->iteration++;
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(255, 255, 0, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    context ctx;
    ctx.renderer = renderer;
    ctx.iteration = 0;
    SDL_Event event;

    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP("assets/sample.bmp");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return 3;
    }
    ctx.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 3;
    }
    SDL_FreeSurface(surface);

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)

    #ifdef __EMSCRIPTEN__
      emscripten_set_main_loop_arg(loop, &ctx, fps, simulate_infinite_loop);
    #else
      while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        loop(&ctx);
        // Delay to keep frame rate constant (using SDL).
        SDL_Delay(20);
      }
    #endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
