//Include SDL functions and datatypes
#include <iostream>
// #include <conio.h>

#define velx 10
#define vely 16
float score=0;
float highscore=0;
#include "include/SDL/SDL.h"
#include "include/SDL/SDL_mixer.h"
#include "include/SDL/SDL_ttf.h"
Mix_Music *bgm = NULL;
Mix_Chunk *sfx[15] = {NULL,NULL,NULL,NULL,NULL,
                      NULL,NULL,NULL,NULL,NULL,
                      NULL,NULL,NULL,NULL,NULL};

#include "helper.h"

#include "tile.h"
#include "character.h"
#include "enemy.h"
#include "powerup.h"
#include "coin.h"
#include "bullet.h"

#include "helper2.h"
#include "mario.h"
#undef main




using namespace std;


void background(SDL_Surface *&bg, SDL_Surface* &screen){
    SDL_BlitSurface(bg,NULL,screen,NULL);
}

void cleanvariables(){
    powerupmax=0;
    bulletmax=0;
    coinmax=0;
    enemymax=0;
    vecmax=0;
    score=0;
}

void credit(SDL_Surface* &screen){
    unsigned int framestart;
    SDL_Surface *creditbg=SDL_LoadBMP("./images/bg6-16.bmp");
    TTF_Init();
    TTF_Font *font= TTF_OpenFont("./ttfs/PressStart2P.ttf",13);
    SDL_Color textColor = {255,255,255};
    
    SDL_Surface *message[5]= {NULL,NULL,NULL,NULL,NULL};
    message[0] = TTF_RenderText_Solid(font, "THANKS TO", textColor);
    message[1] = TTF_RenderText_Solid(font, "BRO YUSTINUS WIDYA WIRATAMA - OOP LECTURES", textColor);
    message[2] = TTF_RenderText_Solid(font, "KHARIS SIMON - CONCEPTS OF GAME LOOP", textColor);
    message[3] = TTF_RenderText_Solid(font, "NINTENDO - ASSETS OF MARIO BROS", textColor);
    message[4] = TTF_RenderText_Solid(font, "FRIENDS - IDEAS", textColor);
    
    SDL_Rect dest[5];
    dest[0].x=340; dest[0].y=490;
    dest[1].x=340; dest[1].y=490+30*1;
    dest[2].x=340; dest[2].y=490+30*2;
    dest[3].x=340; dest[3].y=490+30*3;
    dest[4].x=340; dest[4].y=490+30*4;

    SDL_Event event;
    bool exit=false;
    while(exit==false){
        framestart = SDL_GetTicks();
        background(creditbg,screen);
        
        for(int i=0;i<5;i++){
            if (dest[0].y>200){
                dest[i].y-=30;
            }
            SDL_BlitSurface( message[i],NULL, screen,&dest[i] );
        }
        
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


void instructions(SDL_Surface* &screen){
    unsigned int framestart;
    SDL_Surface *instructions=SDL_LoadBMP("./images/keyboard1.bmp");
    
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

void game(SDL_Surface* &screen){
    int cx=1;
    //GAME BEGINS//
    SDL_Surface *bg=SDL_LoadBMP("./images/bg6-16.bmp");
    /////////////////////////////////////
    TTF_Init();
    TTF_Font *font= TTF_OpenFont("./ttfs/PressStart2P.ttf",13);
    SDL_Color textColor = {255,255,255};
    SDL_Surface *message= NULL;
    SDL_Surface *message2= NULL;
    
    
    SDL_Rect offset;
    offset.x=10; offset.y=10;
    SDL_Rect offset2;
    offset2.x=450; offset2.y=10;
    
    message = TTF_RenderText_Solid(font, "", textColor);
    message2 = TTF_RenderText_Solid(font, "MALIO REMAKE - CUSTOM WORLD", textColor);
    /////////////////////////////////////
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    bgm=Mix_LoadMUS("./sounds/bgm.wav");
    sfx[0]=Mix_LoadWAV("./sounds/smb_jump-small.wav");//smalljump
    sfx[1]=Mix_LoadWAV("./sounds/smb_jump-super.wav");//bigjump
    sfx[2]=Mix_LoadWAV("./sounds/smb_kick.wav");//stomp
    sfx[3]=Mix_LoadWAV("./sounds/smb_coin.wav");//coin
    sfx[4]=Mix_LoadWAV("./sounds/smb_powerup_appears.wav");//powerup appears!
    sfx[5]=Mix_LoadWAV("./sounds/smb_breakblock.wav");//block destroyed
    sfx[6]=Mix_LoadWAV("./sounds/smb_bump.wav");//bump
    sfx[7]=Mix_LoadWAV("./sounds/smb_powerup.wav");//powerup!!
    sfx[8]=Mix_LoadWAV("./sounds/smb_mariodie.wav");//GAME OVER
    sfx[9]=Mix_LoadWAV("./sounds/smb_stage_clear.wav");//powerup appears!
    sfx[10]=Mix_LoadWAV("./sounds/smb3_lost_suit.wav");//powerup lost!
    sfx[11]=Mix_LoadWAV("./sounds/smb_fireball.wav");//fireball!
    
    Mix_VolumeMusic(18*3);
    Mix_PlayMusic(bgm,-1);
    
    
    
    Mario *sprite = new Mario();
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    Uint8 *key;
    unsigned int framestart;
    bool thisone=true;
    char buffer[10];
    char temp[10];
    
    bacaFile();
    while (1){
        if(sprite->get_dead()==true || sprite->get_win()==true){break;}    
        cout<<"SCORE: " <<score*100<<endl;
		framestart = SDL_GetTicks();
		
		if (thisone==true && powerupmax<=0){}
		else if(powerupmax>0 && thisone==true){
            int i=0;
            while(i<powerupmax){
                if(powerup[i]->get_type()==1){
                    bgm=Mix_LoadMUS("./sounds/starman.wav");
                    Mix_PlayMusic(bgm,-1);
                    thisone=false;
                }
                i++;
            }
        }else if(thisone==false && powerupmax<=0){
            bgm=Mix_LoadMUS("./sounds/bgm.wav");
            Mix_PlayMusic(bgm,-1);
            thisone=true;
        }
                
		//update objects
		sprite->think(screen);
		if (coinmax>0)updateCoins(screen);
        if (enemymax>0)updateEnemies(screen);
        if (powerupmax>0)updatePowerUps(screen);
        if (bulletmax>0)updateBullets(screen);
        //UPDATE SCORE
        strcpy(buffer,"SCORE ");
        
        //itoa(score*100,temp,10);
        strcat(buffer, temp);
        message = TTF_RenderText_Solid( font, buffer, textColor );
        
		//draw everything
        moving_bg(cx,bg,screen);    
        printMaps(screen);
        SDL_BlitSurface(message, NULL, screen, &offset);    //print score
        SDL_BlitSurface(message2, NULL, screen, &offset2);  //print headlines
        if (coinmax>0)printCoins(screen);
        if (enemymax>0)printEnemies(screen);
        if (powerupmax>0)printPowerUps(screen);
        if (bulletmax>0)printBullets(screen);
        sprite->drawSprite(screen);
        
        if (sprite->get_batas()){
            score+=0.02;
            geserd(5);
            cx+=5;
            if (cx>1000)cx=1;
            sprite->set_batas(false);
        }
		
		SDL_Flip(screen);
        
		while((SDL_GetTicks()-framestart) < 45);	//keep fps constant copasted from mr google
	}
	
	Mix_VolumeMusic(0);
	if (sprite->get_dead()==true){Mix_PlayChannel(-1,sfx[8],0);SDL_Delay(5000);}
	else if (sprite-> get_win()==true){Mix_PlayChannel(-1,sfx[9],0); SDL_Delay(6000);}
	
    
    
    TTF_CloseFont(font);
    TTF_Quit();
    
    if (score>highscore){
        highscore=score;
        tulisHighScore();       
    }
    cleanvariables();
    Mix_FreeMusic(bgm);
    Mix_CloseAudio();

}


//SDL library REQUIRES this kind of int main()
int main(int argc, char *argv[])
{
    srand(time(NULL));
    //read highscore
    bacaHighScore();
    
    SDL_Surface *screen=NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(1000,480,32,SDL_SWSURFACE);


    SDL_Surface *pointer = NULL;
    
    pointer=SDL_LoadBMP("./images/mushroom.bmp");
    
    Uint32 colorkey = SDL_MapRGB( pointer->format, 0, 0, 255 );// R,G,B yang mau ditransparantkan
	SDL_SetColorKey( pointer, SDL_SRCCOLORKEY, colorkey );      
    int choice=1;
    SDL_Surface *title=SDL_LoadBMP("./images/titlescreen.bmp");

    SDL_Rect offset; offset.x=390; offset.y=420;
    TTF_Init();
    TTF_Font *font= TTF_OpenFont("./ttfs/PressStart2P.ttf",13);
    SDL_Surface *message;
    SDL_Color textColor = {255,255,255};
    char buffer[20];
    char temp[20];
    
    SDL_Event event;
    
    while(1){
        while(SDL_PollEvent(&event)){
                switch (event.type)
                {
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_UP){
                            cout<<choice;
                            choice--;
                            if (choice<1) choice=4;
                        }
                        else if(event.key.keysym.sym == SDLK_DOWN){
                            cout<<choice;
                            choice++;
                            if (choice>4) choice=1;
                        }
                        else if(event.key.keysym.sym == SDLK_RETURN){
                            switch(choice){
                                case 1: 
                                    game(screen);
                                    break;
                                case 2: 
                                    credit(screen);
                                    break;
                                case 3: 
                                    instructions(screen);
                                    break;
                                case 4:
                                    return 0;
                            }
                        }
                        break;
                        
                    case SDL_QUIT: exit(0);
                    break;
                }
        }
        background(title,screen);
        //UPDATE SCORE
        strcpy(buffer,"HIGHSCORE - ");
        //itoa(highscore*100,temp,10);
        strcat(buffer, temp);
        message = TTF_RenderText_Solid( font, buffer, textColor );
        SDL_BlitSurface(message, NULL, screen, &offset);    //print score
        
        switch(choice){
            case 1: 
                apply_cropped_surface(340, 290, 0, 0, pointer, screen);
                break;
            case 2: 
                apply_cropped_surface(340, 320, 0, 0, pointer, screen);
                break;
            case 3: 
                apply_cropped_surface(340, 350, 0, 0, pointer, screen);
                break;
            case 4: 
                apply_cropped_surface(340, 380, 0, 0, pointer, screen);
                break;
        }
        SDL_Flip(screen);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
