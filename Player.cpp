#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Player.h"

Player::Player(int h, int w){
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	velG = 1;
	figura.x = 0;
	figura.y = 0;
	figura.h = h;
	figura.w = w;
	}

void Player::setVelX(int x){
	velX = x;
	}

void Player::setVelY(int y){
	velY = y;
	}
	
void Player::setVelG(int g){
	velG = g;
	}
	
int Player::getVelX(){
	return velX;
	}
	
int Player::getVelY(){
	return velY;
	}
	
int Player::getVelG(){
	return velG;
	}

void Player::move(SDL_Rect *o){
	
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

bool Player::checkColl(SDL_Rect *o){
	SDL_Rect *i;
	
	for(i = o; i < o + OBS; i++){
		if(posX > i->x - figura.w && posX < i->x + i->w && posY > i->y - figura.h && posY < i->y + i->h) //TODO: SEPARAR EN DOS IFs
			return	true;
		}
		
	return	false;
	}
