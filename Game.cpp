#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Jugador.h"

SDL_Window*	window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* pj = NULL;
SDL_Texture* personaje = NULL;

void init(){
	TTF_Init();
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		getchar();
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
		}
	window = SDL_CreateWindow("Fak U Bix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!(window)){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		getchar();
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
		}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return;
	}

void term(){
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	//TTF_CloseFont(Font);
    TTF_Quit();
	SDL_Quit();
	IMG_Quit();
	}

int	main(int argc, char* args[]){
	int	imgFlags = IMG_INIT_PNG,i;
	SDL_Rect obj[OBS]={100, 550, 100, 15, 400, 100, 50, 50, 100, 100, 20, 100, 200, 300, 50, 100};
	SDL_Event e;
	init();
	pj = IMG_Load("PJ.png");
	personaje = SDL_CreateTextureFromSurface(renderer, pj);
	Jugador d(pj->h, pj->w);
	while(!(d.quitFlag)){
		SDL_PollEvent(&e);
		d.quitFlag = d.manageEvent(e);
		d.move(obj);
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	SDL_RenderClear(renderer);
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	for(i=0; i < OBS; i++){
    		SDL_RenderDrawRect(renderer, &obj[i]);
			}
		SDL_RenderCopy(renderer, personaje, NULL, &(d.figura));
		SDL_RenderPresent(renderer);
		}
	term();
	return 0;
	}
