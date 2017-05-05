#include "SDL/SDL.h"

class Bullet:public Character{
    private:
        bool condition;
    public:
        Bullet(int x, int y, bool cond){
            lives=1;
            faceright=false; //ambil y baris pertama
            count=0; // 0-3
            box.x=x;
            box.y=y;
            box.w=32;
            box.h=32;
            
            condition=cond;
            //condition=rand()%2;
            loadSprite("./images/bullet.bmp");
        }
        ~Bullet(){
        }
        void set_condition(bool x){condition=x;}
        bool get_condition(){return condition;}
        
        void set_x(int x){box.x=x;}
        int get_x(){return box.x;}
        
        void set_y(int y){box.y=y;}
        int get_y(){return box.y;}
        
        
        
        void moveLeft(){
            box.x-=velx;
            count++;
            if (count>3) count=0;
        }
        void moveRight(){
            box.x+=velx;
            count++;
            if (count>3) count=0;
        }
        
        void move(){
            if (condition==0){
                moveLeft();
            }else moveRight();
        }
               
        
        
        
        
        
        
        
        
        
        
        
        
        
        
};

