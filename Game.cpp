#include	<stdio.h>
#include	<SDL.h>
#include	<SDL_image.h>
#include	<SDL_ttf.h>

#define	OBS	4

SDL_Window*		window = NULL;
SDL_Renderer*	renderer = NULL;
SDL_Surface*	pj = NULL;
SDL_Texture*	personaje = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const	Uint8* KEYS = SDL_GetKeyboardState(NULL);

class Data{
	public:
		bool quitFlag;
		int posX, posY, velX, velY, velG;
		SDL_Rect figura;
		
		Data(int, int);
		bool checkColl(SDL_Rect *), manageEvent(SDL_Event &);
		//bool manageEvent(SDL_Event &); //TODO: PROBAR ESTO
		void move(SDL_Rect *);
	};

Data::Data(int h, int w){
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

bool Data::manageEvent(SDL_Event &e){
	if(e.type == SDL_QUIT || KEYS[SDL_SCANCODE_ESCAPE])
		return true;
	
	if(KEYS[SDL_SCANCODE_LSHIFT])
		velG=5;
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

void Data::move(SDL_Rect *o){
	
	for(int i = 0, j = 0; i <= velX || j >= velX; i++, j--){
		posX += (velX < 0) ? j : i;
			
		if(posX > 785 || posX < 0 || checkColl(o)){ //TODO: ESTO PUEDE IR A UNA FUNCION
			posX -= (velX < 0) ? j : i;
		}
	}
	
	for(int i = 0, j = 0; i <= velY || j >= velY; i++, j--){
		posY += (velY < 0) ? j : i;
			
		if(posY > 785 || posY < 0 || checkColl(o)){ //TODO: ESTO PUEDE IR A UNA FUNCION
			posY -= (velY < 0) ? j : i;
		}
	}
		
	figura.x = posX;
	figura.y = posY;
	}

bool Data::checkColl(SDL_Rect *o){
	SDL_Rect *i;
	
	for(i = o; i < o + OBS; i++){
		if(posX > i->x - figura.w && posX < i->x + i->w && posY > i->y - figura.h && posY < i->y + i->h) //TODO: SEPARAR EN DOS IFs
			return	true;
		}
		
	return	false;
	}

int	main(int argc, char* args[]){
	int	imgFlags=IMG_INIT_PNG,i;
	SDL_Rect	obj[OBS]={100,550,100,15,400,100,50,50,100,100,20,100,200,300,50,100};
	SDL_Event	e;
	init();
	pj=IMG_Load("PJ.png");
	personaje=SDL_CreateTextureFromSurface(renderer,pj);
	Data	d(pj->h,pj->w);
	while(!(d.quitFlag)){
		SDL_PollEvent(&e);
		d.quitFlag=d.manageEvent(e);
		d.move(obj);
    	SDL_SetRenderDrawColor(renderer,255,255,255,255);
    	SDL_RenderClear(renderer);
    	SDL_SetRenderDrawColor(renderer,0,0,0,255);
    	for(i=0;i<OBS;i++){
    		SDL_RenderDrawRect(renderer,&obj[i]);
			}
		SDL_RenderCopy(renderer,personaje,NULL,&(d.figura));
		SDL_RenderPresent(renderer);
		}
	term();
	return 0;
	}
