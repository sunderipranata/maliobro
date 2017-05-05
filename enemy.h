#include "SDL/SDL.h"

class Enemy:public Character{
    private:
        bool condition;
    public:
        Enemy(int x, int y){
            lives=1;
            faceright=false; //ambil y baris pertama
            count=0;
            box.x=x;
            box.y=y;
            box.w=32;
            box.h=32;
            
            condition=rand()%2;
            loadSprite("./images/enemy.bmp");
        }
        ~Enemy(){
        }
        void set_condition(bool x){condition=x;}
        bool get_condition(){return condition;}
        
        void set_x(int x){box.x=x;}
        int get_x(){return box.x;}
        
        void set_y(int y){box.y=y;}
        int get_y(){return box.y;}
        
        void moveLeft(){
            box.x-=velx;
        }
        void moveRight(){
            box.x+=velx;
        }
        
        void move(){
            count=!count;
            if (condition==0){
                moveLeft();
            }else moveRight();
        }
               
        
        
        
        
        
        
        
        
        
        
        
        
        
};

