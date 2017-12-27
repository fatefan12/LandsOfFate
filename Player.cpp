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
	playerBody.x = 0;
	playerBody.y = 0;
	playerBody.h = h;
	playerBody.w = w;
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
			
		if(posX > SCREEN_WIDTH - playerBody.w || posX < 0 || checkColl(o)){
			posX -= (velX < 0) ? j : i;
		}
	}
	
	for(int i = 0, j = 0; i <= velY || j >= velY; i++, j--){
		posY += (velY < 0) ? j : i;
			
		if(posY > SCREEN_HEIGHT - playerBody.h || posY < 0 || checkColl(o)){
			posY -= (velY < 0) ? j : i;
		}
	}
		
	playerBody.x = posX;
	playerBody.y = posY;
	}

bool Player::checkColl(SDL_Rect *o){
	
	for(SDL_Rect *i = o; i < o + OBS; i++){
		if(posX > i->x - playerBody.w && posX < i->x + i->w)
			if(posY > i->y - playerBody.h && posY < i->y + i->h)
				return	true;
		}
		
	return	false;
	}
