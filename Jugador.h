#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <stdio.h>
#include <SDL.h>

#define	OBS	4
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Jugador{
	public:
		bool quitFlag;
		int posX, posY, velX, velY, velG;
		SDL_Rect figura;
		
		Jugador(int, int);
		bool checkColl(SDL_Rect *), manageEvent(SDL_Event &);
		//bool manageEvent(SDL_Event &); //TODO: PROBAR ESTO
		void move(SDL_Rect *);
	};
#endif  //DATA_H_INCLUDED
