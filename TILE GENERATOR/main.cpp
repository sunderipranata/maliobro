#include <cstdlib>
#include <iostream>
#include "include/SDL/SDL.h"
#include "include/SDL/SDL_mixer"
#include "helper.h"
#include "tiles.h"
#include "helper2.h"


#undef main

using namespace std;
void background(SDL_Surface *&bg, SDL_Surface* &screen){
    SDL_BlitSurface(bg,NULL,screen,NULL);
}

void instructions(SDL_Surface* &screen){
    unsigned int framestart;
    SDL_Surface *instructions=SDL_LoadBMP("./images/keyboard2.bmp");
    
    SDL_Event event;
    bool exit=false;
    while(exit==false){
        framestart = SDL_GetTicks();
        background(instructions,screen);
        
        while(SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_KEYDOWN: exit=true; break;
                    //case SDL_QUIT: exit(0);
                }
                
        }
        
        SDL_Flip(screen);
        while((SDL_GetTicks()-framestart) < 45);
    }
}


int main(int argc, char *argv[]){       
    int cx=1;
    //The main screen
    SDL_Surface *screen=NULL;
    //Start SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Set up screen
    screen=SDL_SetVideoMode(1000,480,32,SDL_SWSURFACE);
    instructions(screen);
    
    Mix_Music *bgm = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    bgm=Mix_LoadMUS("bgm.wav");
    Mix_VolumeMusic(18*3);
    Mix_PlayMusic(bgm,-1);
    //The tile
    //SDL_Surface *tile=NULL;
    //tile=SDL_LoadBMP("./images/grass_tile.bmp");
    
    SDL_Surface *bg=SDL_LoadBMP("./images/bg6-16.bmp");
    
    
    
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    Uint8 *key;
    unsigned int framestart;
    SDL_Event event;
    Uint8 *keystates;
    
    bacaFile();
    
    int posX=0; //posisi buat diwrite ke file. (posisi mouse + posX)
    
    int x = 0, y = 0;//mouse offsets;
    //Tile *obj = new Tile();
    Tile obj;
    int idx=0;
    obj.select(idx);
    int start=0;
    while (1){
		framestart = SDL_GetTicks();
        //handle messages
        keystates = SDL_GetKeyState( NULL );
        if (keystates[SDLK_d]){
            posX+=32;
            cx+=32;
            geser();
            if (cx>1000)cx=0;
        }
        else if (keystates[SDLK_a]){
            posX-=32;
            cx-=32;
            geser();
		    if (cx<0)cx=1000;
        }
        
		while(SDL_PollEvent(&event)){
			if((event.type==SDL_QUIT)) {writeFile(); return 0;}
			if(event.type==SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    emptyFile();
                    bacaFile();
                }
                if(event.key.keysym.sym == SDLK_BACKSPACE){
                    if (start>0){
                        start--;
                        vecmax--;
                        deleteData();
                    }
                }
            }
			if(event.type==SDL_MOUSEMOTION){
                x = event.motion.x;
                y = event.motion.y;
                cout<<x/32*32<<" "<<y/32*32<<endl;
                obj.set_x(((x/32)*32)+posX);
                obj.set_y(((y/32)*32));
            }
            
            if( event.type == SDL_MOUSEBUTTONUP ){
                if( event.button.button == SDL_BUTTON_LEFT ){
                    cout<<"index= "<<obj.get_idx()<<endl;
                    start++;
                    storeData(obj);
                    vec[vecmax]=obj;
                    vecmax++;
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    idx++;
                    if(idx>9)idx=0;
                    obj.select(idx);
                }
            }
        }
    
        //yang digambar itu yg telah di -posX untuk sementara pada tile generator
        //pada game print sesuai X dan Y.
        
        moving_bg(cx,bg,screen);
        printMaps(screen,posX);
        obj.drawSprite(screen, posX);
        
        
        SDL_Flip(screen);
        while((SDL_GetTicks()-framestart) < 180);	//keep framerate constant at 1000/WAITTIME fps
	}
}
