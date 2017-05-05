#include "SDL/SDL.h"

class Character{
    protected:        
        short lives;
        SDL_Surface *karakter;
        int count;
        bool dead;
        SDL_Rect box;
        bool faceright;
    public:
        Character(){
        }
        void set_count(int x){count=x;}
        int get_count(){return count;}
        
        SDL_Rect get_box(){
            return box;
        }
        
        SDL_Surface get_karakter(){return *karakter;}
        
        void set_dead(bool x){dead=x;}
        bool get_dead(){return dead;}
        
        void loadSprite(char x[]){
            karakter = SDL_LoadBMP(x);
            Uint32 colorkey = SDL_MapRGB( karakter->format, 0, 0, 255 );// R,G,B yang mau ditransparantkan
        	SDL_SetColorKey( karakter, SDL_SRCCOLORKEY, colorkey );
        }
        
        void drawSprite(SDL_Surface* &screen){
            if (lives==1)apply_cropped_surface(box.x, box.y, 32*count, 32*(faceright), karakter, screen);
            else if(lives>1)apply_big_mario(box.x, box.y, 32*count, 64*(faceright), karakter, screen);
        } 
        
        bool isDead(){
            if (box.y>500 || box.x<0 || dead==true) return true;
            else return false;
        }
        /*
        //polymorphism
        void drawSprite(SDL_Surface* &screen,int cropH){
            apply_cropped_mario(box.x, box.y, 32*count, 32*(faceright), karakter, screen, cropH);
        } */
             
        
        void freeSurface(){
            SDL_FreeSurface(karakter);
        }
};
