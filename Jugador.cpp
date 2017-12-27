#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Jugador.h"

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

Jugador::Jugador(int h, int w){
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	velG = 1;
	figura.x = 0;
	figura.y = 0;
	figura.h = h;
	figura.w = w;
	quitFlag = 0;
	}

bool Jugador::manageEvent(SDL_Event &e){ //NO TIENE QUE SER UN METODO
	if(e.type == SDL_QUIT || KEYS[SDL_SCANCODE_ESCAPE])
		return true;
	
	if(KEYS[SDL_SCANCODE_LSHIFT])
		velG=2; //METODO DE LA CLASE JUGADOR
	else
		velG=1;
		
	if(KEYS[SDL_SCANCODE_A] || KEYS[SDL_SCANCODE_D]){
		if(KEYS[SDL_SCANCODE_A])
			velX=-velG;
		if(KEYS[SDL_SCANCODE_D])
			velX=velG;
	}
	else
		velX=0;
		
		
	if(KEYS[SDL_SCANCODE_W]||KEYS[SDL_SCANCODE_S]){
		if(KEYS[SDL_SCANCODE_W])
			velY=-velG;
		if(KEYS[SDL_SCANCODE_S])
			velY=velG;
	}
	else
		velY = 0;
		
		
	return false;
	}

void Jugador::move(SDL_Rect *o){
	
	for(int i = 0, j = 0; i <= velX || j >= velX; i++, j--){
		posX += (velX < 0) ? j : i;
			
		if(posX > SCREEN_WIDTH - figura.w || posX < 0 || checkColl(o)){ //TODO: ESTO PUEDE IR A UN METODO
			posX -= (velX < 0) ? j : i;
		}
	}
	
	for(int i = 0, j = 0; i <= velY || j >= velY; i++, j--){
		posY += (velY < 0) ? j : i;
			
		if(posY > SCREEN_HEIGHT - figura.h || posY < 0 || checkColl(o)){ //TODO: ESTO PUEDE IR A UN METODO
			posY -= (velY < 0) ? j : i;
		}
	}
		
	figura.x = posX;
	figura.y = posY;
	}

bool Jugador::checkColl(SDL_Rect *o){
	SDL_Rect *i;
	
	for(i = o; i < o + OBS; i++){
		if(posX > i->x - figura.w && posX < i->x + i->w && posY > i->y - figura.h && posY < i->y + i->h) //TODO: SEPARAR EN DOS IFs
			return	true;
		}
		
	return	false;
	}
