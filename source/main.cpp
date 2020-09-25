
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Game.hpp"
#include <iostream>
#include "Engine/assets/ImageAsset.hpp"

struct context
{
	SDL_Renderer *renderer;
	Game *game;
	SDL_Texture *texture;
	SDL_Window *window;
	SDL_Event event;
	bool quit = false;
	bool fullScreen = false;
	int iteration = 0;
};

void setFullScreen(bool fullScreen, SDL_Window *window)
{
	if (fullScreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
	}
}

void processInput(context *ctx)
{
	SDL_PollEvent(&ctx->event);
	if (ctx->event.type == SDL_QUIT)
	{
		ctx->quit = true;
	}
	if (ctx->event.type == SDL_KEYDOWN && ctx->event.key.keysym.sym == 27)
	{
		ctx->quit = true;
	}
	if (ctx->event.type == SDL_KEYDOWN && ctx->event.key.keysym.sym == 102)
	{
		ctx->fullScreen = !ctx->fullScreen;
		setFullScreen(ctx->fullScreen, ctx->window);
	}
#ifdef __EMSCRIPTEN__
	if (ctx->quit)
	{
		printf("QUITTING \n");
		emscripten_cancel_main_loop();
	}
#endif
}

void loop(void *arg)
{
	context *ctx = static_cast<context *>(arg);
	ctx->game->Loop();
	processInput(ctx);

	SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);
	SDL_RenderClear(ctx->renderer);
	SDL_RenderCopy(ctx->renderer, SINGLETON(AssetLoader)->findAssetByKey<SDL_Texture>("mario"), NULL, NULL);
	SDL_RenderPresent(ctx->renderer);

	ctx->iteration++;
}

int main()
{
	Game game = Game();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return 3;
	}
	context ctx;
	ctx.game = &game;

	if (SDL_CreateWindowAndRenderer(1280, 720, 0, &ctx.window, &ctx.renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s\n", SDL_GetError());
		return 3;
	}
	setFullScreen(ctx.fullScreen, ctx.window);

	SINGLETON(AssetLoader)->addAssetToLoadQueue(new ImageAsset("mario", "assets/mario.png", ctx.renderer));
	SINGLETON(AssetLoader)->loadAll();

	const int simulate_infinite_loop = 1; // call the function repeatedly
	const int fps = -1;										// call the function as fast as the browser wants to render (typically 60fps)

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(loop, &ctx, fps, simulate_infinite_loop);
#else
	while (1)
	{
		loop(&ctx);
		// Delay to keep frame rate constant (using SDL).
		SDL_Delay(20);
		if (ctx.quit)
		{
			break;
		}
	}
#endif

	SDL_DestroyRenderer(ctx.renderer);
	SDL_DestroyWindow(ctx.window);
	SDL_Quit();
	printf("EXIT \n");

	return EXIT_SUCCESS;
}
