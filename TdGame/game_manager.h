#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "manager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;
public:

	int run(int argc, char** argv)
	{
		Uint64 last_conter = SDL_GetPerformanceCounter();
		const Uint64 counter_freq = SDL_GetPerformanceFrequency();

		while (!is_quit)
		{
			while (SDL_PollEvent(&event))
				on_input();
			Uint64 current_conter = SDL_GetPerformanceCounter();
			double delta = (double)(current_conter - last_conter) / counter_freq;
			last_conter = current_conter;
			if (delta * 1000 < 1000.0 / 60)
				SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

			//更新数据
			on_update(delta);

			//绘制画面

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			on_render();

			SDL_RenderPresent(renderer);



		}
		return 0;
	}

protected:
	GameManager()
	{

		init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 init false!");
		init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image init false!");
		init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer init false!");
		init_assert(!TTF_Init(), u8"SDL_ttf init false!");

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

		window = SDL_CreateWindow(u8"村庄保卫战！", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		init_assert(window, u8"create game window false");

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

		init_assert(renderer, u8"renderer init false!");
	}

	~GameManager()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

private:

	SDL_Event event;
	bool is_quit;

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;


private:
	void init_assert(bool flag, const char* err_msg)
	{
		if (flag) return;

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"GAME START FALSE", err_msg, window);
		exit(-1);
	}

	void on_input()
	{

	}


	void on_update(double delta)
	{

	}

	void on_render()
	{

	}
};



#endif // !_GAME_MANAGER_H

