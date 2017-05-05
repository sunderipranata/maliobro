#include "SDL/SDL.h"

class PowerUp:public Character{
    private:
        bool condition;
        bool type;//0 untuk mushroom, 1 untuk starman
    public:
        PowerUp(int x, int y, bool tipe){
            lives=1;
            faceright=false; //ambil y baris pertama
            count=0;
            box.x=x;
            box.y=y;
            box.w=32;
            box.h=32;
            type=tipe;
            condition=1;//rand()%2;
            if (tipe==0) loadSprite("./images/mushroom.bmp");
            else if (tipe==1)loadSprite("./images/star.bmp");
        }
        ~PowerUp(){
        }
        void set_condition(bool x){condition=x;}
        bool get_condition(){return condition;}
        
        //void set_type(bool x){type=x;}
        bool get_type(){return type;}
        
        void set_x(int x){box.x=x;}
        int get_x(){return box.x;}
        
        void set_y(int y){box.y=y;}
        int get_y(){return box.y;}
        
        
        
        void moveLeft(){
            box.x-=velx;
            if (type==1){
                count++;
                if (count>3) count=0;
            }
        }
        void moveRight(){
            box.x+=velx;
            if (type==1){
                count++;
                if (count>3) count=0;
            }
        }
        
        void move(){
            if (condition==0){
                moveLeft();
            }else moveRight();
        }
               
        
        
        
        
        
        
        
        
        
        
        
        
        
        
};

