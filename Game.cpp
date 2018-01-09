#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Player.h"

SDL_Window*	window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* pl = NULL;
SDL_Texture* playerTexture = NULL;

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

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
	
bool manageEvent(SDL_Event &e, Player *player){
	if(e.type == SDL_QUIT || KEYS[SDL_SCANCODE_ESCAPE])
		return true;
	
	
	if(KEYS[SDL_SCANCODE_LSHIFT]){
		player->setVelG(2);
		}
	else{
		player->setVelG(1);
		}


	if(KEYS[SDL_SCANCODE_A])
		player->setVelX(player->getVelG() * -1);
		
	else if(KEYS[SDL_SCANCODE_D])
		player->setVelX(player->getVelG());
		
	else
		player->setVelX(0);


	if(KEYS[SDL_SCANCODE_W])
		player->setVelY(player->getVelG() * -1);
		
	else if(KEYS[SDL_SCANCODE_S])
		player->setVelY(player->getVelG());
		
	else
		player->setVelY(0);
		
		
	return false;
	}

int	main(int argc, char* args[]){
	bool quitFlag = 0;
	int	imgFlags = IMG_INIT_PNG,i;
	SDL_Rect structure[OBS] = {100, 550, 100, 15, 400, 100, 50, 50, 100, 100, 20, 100, 200, 300, 50, 100}; //PASAR A CLASE
	SDL_Event e;
	init();
	pl = IMG_Load("PJ.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, pl);
	Player player(pl->h, pl->w);
	while(!quitFlag){
		SDL_PollEvent(&e);
		quitFlag = manageEvent(e, &player);
		player.move(structure);
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	SDL_RenderClear(renderer);
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	for(i=0; i < OBS; i++){
    		SDL_RenderDrawRect(renderer, &structure[i]);
			}
		SDL_RenderCopy(renderer, playerTexture, NULL, &(player.playerBody));
		SDL_RenderPresent(renderer);
		}
	term();
	return 0;
	}
