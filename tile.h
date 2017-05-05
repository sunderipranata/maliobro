#include "SDL/SDL.h"

class Tile{
    SDL_Surface *image;
    protected:
        int index;
        //0 ground
        //1 block
        //2 wall1
        //3 wall2
        //4 wall3
        //5 mystery box
        //6 brick
        //7 enemy
        //8 coin
        //9 house
        SDL_Rect size; //area print
    public:
        void set_x(int x){size.x=x;}
        void set_y(int y){size.y=y;}
        void set_idx(int x){index=x;}
        int get_x(){return size.x;}
        int get_y(){return size.y;}
        int get_idx(){return index;}
            
        void drawSpriteReal(SDL_Surface* &screen){
            apply_cropped_tile(size.x, size.y, size.w, size.h, image, screen);
        }
        SDL_Rect get_size(){return size;}
        ~Tile(){//Tidak benar2 me-delete tapi hanya menghilangkan.
            size.x=0;
            size.y=0;
            size.w=0;
            size.h=0;
        }
        Tile(int idx, int x, int y){
            size.x=x;
            size.y=y;
            switch(idx){
                case 0:
                    index=0;
                    size.w=32;
                    size.h=32;
                    image = SDL_LoadBMP("./images/ground.bmp"); break;    
                case 1:
                    index=1;
                    size.w=32;
                    size.h=32;
                    image = SDL_LoadBMP("./images/block.bmp"); break;
                case 2:
                    index=2;
                    size.w=64;
                    size.h=64;
                    image = SDL_LoadBMP("./images/wall1.bmp"); break;
                case 3:
                    index=3;
                    size.w=64;
                    size.h=96;
                    image = SDL_LoadBMP("./images/wall2.bmp"); break;
                case 4:
                    index=4;
                    size.w=64;
                    size.h=128;
                    image = SDL_LoadBMP("./images/wall3.bmp"); break;
                case 5:
                    index=5;
                    size.w=32;
                    size.h=32;
                    image = SDL_LoadBMP("./images/mysterybox.bmp"); break;
                case 6:
                    index=6;
                    size.w=32;
                    size.h=32;
                    image = SDL_LoadBMP("./images/brick.bmp"); break;
                //case 7 enemy
                //case 8 coin
        	    case 9:
                    index=9;
                    size.w=128;
                    size.h=128;
                    image = SDL_LoadBMP("./images/house.bmp"); break;
            }
        }
        
        void deadMysteryBox(){
            index=10;
            //size.w=32;
            //size.h=32;
            image = SDL_LoadBMP("./images/deadmysterybox.bmp");
        }
       
};
