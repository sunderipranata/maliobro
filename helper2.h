#include <fstream>
#include <queue>
//declaring global variables//
Tile *vec[2000];
Enemy *enemy[100];
Coin *coin[1000];
int coinmax=0;
int enemymax=0;
int vecmax=0;

Bullet *bullet[5];//maksimal yang dikeluarkan adalah 3, 2 buat jaga2~ jaga apa?
int bulletmax=0;

PowerUp *powerup[10];
int powerupmax=0;

void bacaFile(){
    std::ifstream in;
    std::string str;
	in.open ("./TILE GENERATOR/maps/example.txt");
	
	int i=0;
	int x[2];
	int idx,vx,vy;
	while(std::getline(in, str, '#').good()){
        x[i]=atoi(str.c_str());
        switch(i){
            case 0: idx=x[i]; break;
            case 1: vx=x[i];  break;
            case 2: vy=x[i];  break;
        }
        i++;
        if (i>2) {
            vec[vecmax]=new Tile(idx,vx,vy);
            i=0;
            vecmax++;
        }
    }
	in.close();
	///////////////////////////////////////////////////////////
	//READING MONSTER FILE
	std::ifstream in2;
    std::string str2;
	in2.open ("./TILE GENERATOR/monsters/monster.txt");
	
	int i2=0;
	int x2[2];
	int idx2,vx2,vy2;
	while(std::getline(in2, str2, '#').good()){
        x2[i2]=atoi(str2.c_str());
        switch(i2){
            case 0: idx=x[i2];break;
            case 1: vx2=x2[i2];  break;
            case 2: vy2=x2[i2];  break;
        }
        i2++;
        if (i2>2) {
            std::cout<<"X,Y "<<vx2<<" "<<vy2;
            enemy[enemymax]=new Enemy(vx2,vy2);
            i2=0;
            enemymax++;
        }
    }
	in2.close();
	
	///////////////////////////////////////////////////////////
	//READING COIN FILE
	std::ifstream in3;
    std::string str3;
	in3.open ("./TILE GENERATOR/coins/coin.txt");
	
	int i3=0;
	int x3[2];
	int idx3,vx3,vy3;
	while(std::getline(in3, str3, '#').good()){
        x3[i3]=atoi(str3.c_str());
        switch(i3){
            case 0: idx=x[i3];break;
            case 1: vx3=x3[i3];  break;
            case 2: vy3=x3[i3];  break;
        }
        i3++;
        if (i3>2) {
            std::cout<<"X,Y "<<vx3<<" "<<vy3;
            coin[coinmax]=new Coin(vx3,vy3);
            i3=0;
            coinmax++;
        }
    }
	in3.close();
}

void printMaps(SDL_Surface* &screen){
    int i=0;
    while(i<vecmax){
        vec[i]->drawSpriteReal(screen);
        i++;
    }
}

void updateEnemies(SDL_Surface* &screen){
    for(int i=0;i<enemymax;i++){
        if (enemy[i]->isDead()){
            delete enemy[i];
            enemymax--;
            for(int j=i;j<enemymax;j++){
                enemy[j]=enemy[j+1];
            }
        }
        std::cout<<"ENEMY MAX: "<<enemymax<<std::endl;
    } 
    for(int i=0;i<enemymax;i++){
        for(int j=0;j<vecmax;j++){
            if(check_collision(enemy[i]->get_box(), vec[j]->get_size())){
                if(enemy[i]->get_condition()==0)
                    enemy[i]->set_x(enemy[i]->get_x()+velx);
                else
                    enemy[i]->set_x(enemy[i]->get_x()-velx);
                    
                enemy[i]->set_condition(!(enemy[i]->get_condition()));
                break;
            }
        }
    }
    for(int i=0;i<enemymax;i++){
        enemy[i]->move();
        enemy[i]->set_y(enemy[i]->get_y()+vely);//this is called GRAVITY!
    }
    for(int i=0;i<enemymax;i++){
        for(int j=0;j<vecmax;j++){
            if (check_collision(enemy[i]->get_box(),vec[j]->get_size()) && (enemy[i]->get_box()).y < (vec[j]->get_size()).y){
                enemy[i]->set_y(enemy[i]->get_y()-vely);
            }
        }
    }
}

void printEnemies(SDL_Surface* &screen){
    int i=0;
    while(i<enemymax){
        enemy[i]->drawSprite(screen);
        i++;
    }
}


void updatePowerUps(SDL_Surface* &screen){
    for(int i=0;i<powerupmax;i++){
        if (powerup[i]->isDead()){
            delete powerup[i];
            powerupmax--;
            for(int j=i;j<powerupmax;j++){
                powerup[j]=powerup[j+1];
            }
        }
        std::cout<<"powerup MAX: "<<powerupmax<<std::endl;
    } 
    for(int i=0;i<powerupmax;i++){
        for(int j=0;j<vecmax;j++){
            if(check_collision(powerup[i]->get_box(), vec[j]->get_size())){
                if(powerup[i]->get_condition()==0)
                    powerup[i]->set_x(powerup[i]->get_x()+velx);
                else
                    powerup[i]->set_x(powerup[i]->get_x()-velx);
                    
                powerup[i]->set_condition(!(powerup[i]->get_condition()));
                break;
            }
        }
    }
    for(int i=0;i<powerupmax;i++){
        powerup[i]->move();
        powerup[i]->set_y(powerup[i]->get_y()+vely);//this is called GRAVITY!
    }
    for(int i=0;i<powerupmax;i++){
        for(int j=0;j<vecmax;j++){
            if (check_collision(powerup[i]->get_box(),vec[j]->get_size()) && (powerup[i]->get_box()).y < (vec[j]->get_size()).y){
                powerup[i]->set_y(powerup[i]->get_y()-vely);
            }
        }
    }
}

void printPowerUps(SDL_Surface* &screen){
    int i=0;
    while(i<powerupmax){
        powerup[i]->drawSprite(screen);
        i++;
    }
}

void updateBullets(SDL_Surface* &screen){
    //check if the bullets dead by going far down
    for(int i=0;i<bulletmax;i++){
        if (bullet[i]->isDead()){
            delete bullet[i];
            bulletmax--;
            for(int j=i;j<bulletmax;j++){
                bullet[j]=bullet[j+1];
            }
        }
        std::cout<<"bullet MAX: "<<bulletmax<<std::endl;
    }
    //check to be dead if collide with any tiles
    for(int i=0;i<bulletmax;i++){
        for(int j=0;j<vecmax;j++){
            if(check_collision(bullet[i]->get_box(), vec[j]->get_size())){
                delete bullet[i];
                bulletmax--;
                for(int j=i;j<bulletmax;j++){
                    bullet[j]=bullet[j+1];
                }
            }
        }
        //kill enemy!!!!!!
        for(int j=0;j<enemymax;j++){
            if(check_collision(bullet[i]->get_box(), enemy[j]->get_box())){
                Mix_PlayChannel(-1,sfx[2],0);
                delete bullet[i];
                bulletmax--;
                for(int j=i;j<bulletmax;j++){
                    bullet[j]=bullet[j+1];
                }
                delete enemy[i];
                enemymax--;
                for(int j=i;j<enemymax;j++){
                    enemy[j]=enemy[j+1];
                }
            }
        }
    }
    //apply the gravity and movements
    for(int i=0;i<bulletmax;i++){
        bullet[i]->move();
        bullet[i]->set_y(bullet[i]->get_y()+vely);//this is called GRAVITY!
    }
    //set to be always above the tiles
    for(int i=0;i<bulletmax;i++){
        for(int j=0;j<vecmax;j++){
            if (check_collision(bullet[i]->get_box(),vec[j]->get_size()) && (bullet[i]->get_box()).y < (vec[j]->get_size()).y){
                bullet[i]->set_y(bullet[i]->get_y()-vely);
            }
        }
    }
}

void printBullets(SDL_Surface* &screen){
    int i=0;
    while(i<bulletmax){
        bullet[i]->drawSprite(screen);
        i++;
    }
}


void updateCoins(SDL_Surface* &screen){    
    for(int i=0;i<coinmax;i++){
        if (coin[i]->get_count()<=3)
            coin[i]->set_count(coin[i]->get_count()+1);
        else {    
                if (coin[i]->get_temporary()==true){
                delete coin[i];
                coinmax--;
                for(int j=i;j<coinmax;j++){
                    coin[j]=coin[j+1];
                }
            }
            else coin[i]->set_count(0);
        }
    }        
}

void printCoins(SDL_Surface* &screen){
    int i=0;
    while(i<coinmax){
        coin[i]->drawSprite(screen);
        i++;
    }
}


void geserd(int geser){
    int i=0;
    while(i<vecmax){
        vec[i]->set_x(vec[i]->get_x()-geser);
        i++;
    }
    i=0;
    while(i<enemymax){
        enemy[i]->set_x(enemy[i]->get_x()-geser);
        i++;
    }
    i=0;
    while(i<coinmax){
        coin[i]->set_x(coin[i]->get_x()-geser);
        i++;
    }
    i=0;
    while(i<powerupmax){
        powerup[i]->set_x(powerup[i]->get_x()-geser);
        i++;
    }
    i=0;
    while(i<bulletmax){
        bullet[i]->set_x(bullet[i]->get_x()-geser);
        i++;
    }
}








void bacaHighScore(){
    std::ifstream in;
    std::string str;
    in.open ("./highscore/highscore.txt");
	while(std::getline(in, str).good()){
        std::cout<<"it was here!"; 
        highscore=atoi(str.c_str());
    }
	in.close();
}
void tulisHighScore(){
    //WRITE THE LOCATION OF SPAWNING MONSTERS    
    std::ofstream myfile;
    myfile.open("./highscore/highscore.txt");
    
    if (myfile.is_open()){
        std::cout<<"here";
        myfile << highscore<<"\n";
    }else std::cout << "Unable to open file";
        
    myfile.close();
}
