#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <stdio.h>
#include <SDL.h>

#define	OBS	4
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Player{
	public:
		//CLASS PROPERTIES
		int posX, posY, velX, velY, velG;
		SDL_Rect figura;
		
		//CLASS METHODS
		Player(int, int);
		bool checkColl(SDL_Rect *), manageEvent(SDL_Event &);
		void move(SDL_Rect *);
		
		//GETTERS AND SETTERS
		void setVelX(int);
		void setVelY(int);
		void setVelG(int);
		int getVelX(void);
		int getVelY(void);
		int getVelG(void);
	};
#endif  //DATA_H_INCLUDED
