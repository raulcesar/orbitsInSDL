#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.hpp"



int main(int, char**) {
	const int SCREEN_WIDTH  = 640;
	const int SCREEN_HEIGHT = 480;
 

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	SDL_Window *win = SDL_CreateWindow("Hello Orbit Wim!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		cleanup(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::string imagePath = getResourcePath() + "sample.png";
	// SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	// if (bmp == nullptr) {
	// 	cleanup(ren, win);
	// 	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
	// 	SDL_Quit();
	// 	return 1;
	// }


	SDL_Texture *tex = IMG_LoadTexture(ren, imagePath.c_str());

	// SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	// SDL_FreeSurface(bmp);
	// cleanup(bmp);
	if (tex == nullptr) {
		cleanup(ren, win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}



	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				quit = true;
			}
		}

		SDL_RenderClear(ren);
		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren);
	}


	cleanup(tex, ren, win);

	SDL_Quit();
	return 0;
}