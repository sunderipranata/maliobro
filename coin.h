#include "SDL/SDL.h"

class Coin:public Character{
    private:
        bool temporary;
    public:
        Coin(int x, int y){
            lives=1;
            
            temporary=false;
            faceright=false; //ambil y baris pertama
            count=0;
            box.x=x;
            box.y=y;
            box.w=32;
            box.h=32;
            
            loadSprite("./images/coin.bmp");
        }
        ~Coin(){
        }
        void set_temporary(bool x){temporary=x;}
        int get_temporary(){return temporary;}
        
        void set_x(int x){box.x=x;}
        int get_x(){return box.x;}
        
        void set_y(int y){box.y=y;}
        int get_y(){return box.y;}
};

