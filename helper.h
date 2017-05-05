#include "SDL/SDL.h"
//#include <iostream>
void apply_cropped_surface(int posX, int posY,  int cropX, int cropY, SDL_Surface *image, SDL_Surface *screen){
    SDL_Rect crop;
    
    crop.x=cropX;
    crop.y=cropY;
    crop.w=32;
    crop.h=32;
    
    SDL_Rect position;
    position.x=posX;
    position.y=posY;
    
    SDL_BlitSurface(image, &crop, screen, &position);    
}

void apply_big_mario(int posX, int posY,  int cropX, int cropY, SDL_Surface *image, SDL_Surface *screen){
    SDL_Rect crop;
    
    crop.x=cropX;
    crop.y=cropY;
    crop.w=32;
    crop.h=64;
    
    SDL_Rect position;
    position.x=posX;
    position.y=posY;
    
    SDL_BlitSurface(image, &crop, screen, &position);    
}

void apply_cropped_tile(int posX, int posY,  int cropW, int cropH, SDL_Surface *image, SDL_Surface *screen){
    SDL_Rect crop;
    
    crop.x=0;
    crop.y=0;
    crop.w=cropW;
    crop.h=cropH;
    
    SDL_Rect position;
    position.x=posX;
    position.y=posY;
    
    SDL_BlitSurface(image, &crop, screen, &position);    
}

void moving_bg(int cropX, SDL_Surface *bg, SDL_Surface *screen){
    SDL_Rect crop;
    
    crop.x=cropX;
    crop.y=1;
    crop.w=1000;
    crop.h=600;
    
    SDL_BlitSurface(bg, &crop, screen, NULL); 
}


bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB ) //dirancang secara khusus~
    {
        return false;
    }
    
    if( topA >= bottomB ) //dirancang secara khusus~
    {
        return false;
    }
    
    if( rightA <= leftB+velx )
    {
        return false;
    }
    
    if( leftA >= rightB-velx )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}









