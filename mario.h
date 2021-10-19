
#include "include/SDL/SDL.h"
#define SMALL_JUMP 128
#define BIG_JUMP 160
class Mario:public Character{
    private:
        bool win;
        int JUMP;
        bool down;
        bool batas;
        bool upstairs;
        int imaboveidx;
        int temp;
        bool lockjump;
        Uint8 *keystates;
        SDL_Event event;
    public:
        Mario(){
            win=false;
            JUMP=SMALL_JUMP;
            lives=1;
            loadSprite("./images/mario.bmp");
            dead=false;
            imaboveidx=-1;
            temp=0;
            upstairs=false;
            batas=false;
            box.x=50;
            box.y=400;
            count=5;
            lockjump=true;
            down = true;
            faceright=true;
            box.x = 50;
            box.y = 0;
            box.w = 32;//CHAR_WIDTH;
            box.h = 32;//CHAR_HEIGHT;
        }
        bool get_batas(){return batas;}
        void set_batas(bool x){batas=x;}
        bool get_win(){return win;}
        
        bool get_lockjump(){return lockjump;}
        
        void moveRight(){
            if (box.x<400){
                box.x+=velx;
            }
            for (int i=0;i<vecmax;i++)
            if(check_collision(box, vec[i]->get_size())){
                if (vec[i]->get_idx()==9){
                    //Mix_PlayChannel(-1,sfx[9],0);
                    //SDL_Delay(5000);
                    win=true;
                    //count=5;
                }
                box.x-=velx;
                break;
            }
            
            if (box.x>=400) batas=true;
        }
        
        void moveLeft(){
            if (box.x>=0){
                box.x-=velx;
            }
            for (int i=0;i<vecmax;i++)
            if(check_collision(box, vec[i]->get_size())){
                box.x+=velx;
                break;
            }
            
            if (box.x>=0 ) batas=false;
        }
        
        void think(SDL_Surface* &screen){
            //if collide with coins
            for (int i=0;i<coinmax;i++)
            if(check_collision(box, coin[i]->get_box())){
                Mix_PlayChannel(-1,sfx[3],0);
                delete coin[i];
                coinmax--;
                for(int j=i;j<coinmax;j++){
                    coin[j]=coin[j+1];
                }
                score++;
                break;
            }
            std::cout<<"live: " << lives;
            
            //if collide with enemies
            for (int i=0;i<enemymax;i++)
            if(check_collision(box, enemy[i]->get_box())){
                lives--;
                if (lives==2) {
                    Mix_PlayChannel(-1,sfx[10],0);
                    loadSprite("./images/mario2.bmp");
                }
                else if (lives==1) {
                    Mix_PlayChannel(-1,sfx[10],0);
                    loadSprite("./images/mario.bmp");
                    box.y+=32;
                    box.h-=32;
                    JUMP=SMALL_JUMP;
                }
                else if (lives==0){dead=true; break;}
                
                delete enemy[i];
                enemymax--;
                for(int j=i;j<enemymax;j++){
                    enemy[j]=enemy[j+1];
                }
                break;
            }
            //if collide with powerups
            for (int i=0;i<powerupmax;i++)
            if(check_collision(box, powerup[i]->get_box())){
                Mix_PlayChannel(-1,sfx[7],0);      
                if (lives==3){}
                else if(powerup[i]->get_type()==1) {
                    if(lives==1){
                        box.y-=32;
                        box.h+=32;
                        JUMP=BIG_JUMP;
                    }   
                    lives=3;
                    loadSprite("./images/mario3.bmp"); 
                }
                else if(lives==1 && powerup[i]->get_type()==0) {
                    lives=2;
                    loadSprite("./images/mario2.bmp");
                    box.y-=32;
                    box.h+=32;
                    JUMP=BIG_JUMP;
                }
                
                delete powerup[i];
                powerupmax--;
                for(int j=i;j<powerupmax;j++){
                    powerup[j]=powerup[j+1];
                }
                
                break;
            } 
            
            if (lockjump==true){
                count=0;
                if (box.y<=temp-JUMP) {down=true;} //350 buat atur ketinggian lompat
                else if (box.y>500){down=false; lockjump=false; imaboveidx=-1; dead=true;}
                
                if (down) box.y+=vely; //turun
                else box.y-=vely;
                
                for (int i=0;i<vecmax;i++)
                if (check_collision(box,vec[i]->get_size()) && box.y<(vec[i]->get_size()).y){
                    std::cout<<" IM UPSTAIRS ";
                    box.y-=vely;
                    upstairs=true;
                    down=false;
                    lockjump=false;
                    imaboveidx=i;
                    break;
                }
                
                for (int i=0;i<enemymax;i++)
                if (check_collision(box,enemy[i]->get_box()) && box.y<(enemy[i]->get_box()).y){
                    Mix_PlayChannel(-1,sfx[2],0);
                    delete enemy[i];
                    enemymax--;
                    for(int j=i;j<enemymax;j++){
                        enemy[j]=enemy[j+1];
                    }
                    std::cout<<" IM above ENEMY";
                    box.y-=vely;
                    upstairs=true;
                    down=false;
                    lockjump=false;
                    imaboveidx=i;
                    break;
                }
                
                for (int i=0;i<vecmax;i++)
                if (check_collision(box,vec[i]->get_size())){
                    if (vec[i]->get_idx()== 5){
                        if (rand()%1==0){//probability dapat star 1/30
                            Mix_PlayChannel(-1,sfx[4],0);
                            powerup[powerupmax] = new PowerUp(vec[i]->get_x(),vec[i]->get_y()-32,1);
                            powerupmax++;
                            vec[i]->deadMysteryBox();
                        }
                        else if (rand()%20==5){//probability dapat powerup 1/20
                            Mix_PlayChannel(-1,sfx[4],0);
                            powerup[powerupmax] = new PowerUp(vec[i]->get_x(),vec[i]->get_y()-32,0);
                            powerupmax++;
                            vec[i]->deadMysteryBox();
                        }else{
                            Mix_PlayChannel(-1,sfx[3],0);
                            coin[coinmax] = new Coin(vec[i]->get_x(),vec[i]->get_y()-32);
                            coin[coinmax]->set_temporary(true);
                            coinmax++;
                            score++;
                        }
                        if (rand()%5==2){//probability mysterybox mati 1/5
                            vec[i]->deadMysteryBox();
                        }
                    }
                    else if (vec[i]->get_idx()== 1 && lives>1){
                        Mix_PlayChannel(-1,sfx[5],0);
                        delete vec[i];
                    }
                    else if (vec[i]->get_idx()== 1)Mix_PlayChannel(-1,sfx[6],0);
                    std::cout<<"HEADBUTT!";
                    box.y+=vely;
                    down=true;
                }
                
        
            }else if (upstairs==true){
                if (box.x>(vec[imaboveidx]->get_size()).x+(vec[imaboveidx]->get_size()).w || box.x+box.w < (vec[imaboveidx]->get_size()).x){
                    std::cout<<"GRAVITY!!!!!";
                    down=true;
                    lockjump=true;
                    upstairs=false;
                } 
            }
            
            
            keystates = SDL_GetKeyState( NULL );
            if(keystates[SDLK_RIGHT]){
                if (lockjump==false)count++;
                if (count>4) count=0;
        		moveRight();
                faceright = true;
                std::cout<<"kanan";
        	}else if(keystates[SDLK_LEFT]){
                if (lockjump==false)count++;
                if (count>4) count=0;
        		moveLeft();
                faceright = false;
                std::cout<<"kiri";
        	}else if (lockjump==true) count=5;//agak aneh? entahlah~
            else count = 4;
            
        	while(SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_SPACE && lockjump==false){
                            if (lives>1)Mix_PlayChannel(-1,sfx[1],0); //bigjump sound
                            else Mix_PlayChannel(-1,sfx[0],0); //smalljump sound
                            lockjump=true;
                    	    temp=box.y;
                    	    std::cout<<"space";
                        }
                        else if(event.key.keysym.sym == SDLK_x && bulletmax<3 && lives>2){
                            Mix_PlayChannel(-1,sfx[11],0);
                            bullet[bulletmax] = new Bullet(box.x+32,box.y+32,faceright);
                            bulletmax++;
                        }
                        break;
                        
                    case SDL_QUIT: exit(0);
                    break;
                }
            }
            
        }
        
};
