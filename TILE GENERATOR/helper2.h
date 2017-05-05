#include <fstream>
#include <vector>
#include <stack>          

std::stack<Tile> mystack;
std::stack<Tile> mystack2;
std::stack<Tile> mystack3;

Tile vec[2000];
int vecmax=0;

void storeData(Tile obj){
    if (obj.get_idx()==7){
        mystack2.push(obj);    
    }
    else if (obj.get_idx()==8){
        mystack3.push(obj);    
    }
    else{        
        mystack.push(obj);
    }
}

void deleteData(){
    if (vec[vecmax].get_idx()==7){
        mystack2.pop();    
    }
    else if (vec[vecmax].get_idx()==8){
        mystack3.pop();    
    }
    else{        
        mystack.pop();
    }
}   

void emptyFile(){
    //WRITE THE LOCATION OF TILES
    std::ofstream myfile ("./maps/example.txt");
    myfile.close();
    
    //WRITE THE LOCATION OF SPAWNING MONSTERS
    std::ofstream myfile2 ("./monsters/monster.txt");
    myfile2.close();
    
    //WRITE THE LOCATION OF SPAWNING COINS
    std::ofstream myfile3 ("./coins/coin.txt");
    myfile3.close();
    
    while(!mystack.empty()){
        mystack.pop();
    }
    while(!mystack2.empty()){
        mystack.pop();
    }
    while(!mystack3.empty()){
        mystack.pop();
    }
    
    vecmax=0;
}  

void writeFile(){
    //WRITE THE LOCATION OF SPAWNING MONSTERS    
    std::ofstream myfile ("./maps/example.txt", std::ios_base::app);
    while(!mystack.empty()){
        Tile temp;
        temp = mystack.top();
        //std::cout<<std::endl<<temp.get_idx()<<std::endl;
        //WRITE TO FILE HERE
        if (myfile.is_open()){
            myfile << temp.get_idx()<<"#"<<temp.get_x()<<"#"<<temp.get_y()<<"#\n";
        }else std::cout << "Unable to open file";
        
        mystack.pop();
    }
    myfile.close();
    //////////////////////////////////////////////////////////////////////////////////////////
    
    //WRITE THE LOCATION OF SPAWNING MONSTERS
    std::ofstream myfile2 ("./monsters/monster.txt", std::ios_base::app);
    while(!mystack2.empty()){
        Tile temp;
        temp = mystack2.top();
        //std::cout<<std::endl<<temp.get_idx()<<std::endl;
        //WRITE TO FILE HERE
        if (myfile2.is_open()){
            myfile2 << temp.get_idx()<<"#"<<temp.get_x()<<"#"<<temp.get_y()<<"#\n";
        }else std::cout << "Unable to open file";
        
        mystack2.pop();
    }
    myfile2.close();
    
    //WRITE THE LOCATION OF SPAWNING COINS
    std::ofstream myfile3 ("./coins/coin.txt", std::ios_base::app);
    while(!mystack3.empty()){
        Tile temp;
        temp = mystack3.top();
        //std::cout<<std::endl<<temp.get_idx()<<std::endl;
        //WRITE TO FILE HERE
        if (myfile3.is_open()){
            myfile3 << temp.get_idx()<<"#"<<temp.get_x()<<"#"<<temp.get_y()<<"#\n";
        }else std::cout << "Unable to open file";
        
        mystack3.pop();
    }
    myfile3.close();
}  




void bacaFileCoin(){
    std::ifstream in;
    std::string str;
    in.open ("./coins/coin.txt");
	int i=0;
	int x[2];
	
	while(std::getline(in, str, '#').good()){
        std::cout<<"it was here!"; 
        Tile temp;
        x[i]=atoi(str.c_str());
        switch(i){
            case 0: temp.set_idx(x[i]); temp.select(x[i]); break;
            case 1: temp.set_x(x[i]); break;
            case 2: temp.set_y(x[i]); break;
        }
        i++;
        if (i>2) {
            std::cout<<"haho";
            std::cout<<vecmax;
            i=0;
            vec[vecmax]=temp;
            vecmax++;
        }
    }
	in.close();
	
}

void bacaFileMonster(){
    std::ifstream in;
    std::string str;
	in.open ("./monsters/monster.txt");
	int i=0;
	int x[2];
	
	while(std::getline(in, str, '#').good()){
        std::cout<<"it was here!"; 
        Tile temp;
        x[i]=atoi(str.c_str());
        switch(i){
            case 0: temp.set_idx(x[i]); temp.select(x[i]); break;
            case 1: temp.set_x(x[i]); break;
            case 2: temp.set_y(x[i]); break;
        }
        i++;
        if (i>2) {
            std::cout<<"haho";
            std::cout<<vecmax;
            i=0;
            vec[vecmax]=temp;
            vecmax++;
        }
    }
	in.close();
	
	bacaFileCoin();
}

void bacaFile(){
    std::ifstream in;
    std::string str;
	in.open ("./maps/example.txt");
	
	int i=0;
	int x[2];
	
	while(std::getline(in, str, '#').good()){
        std::cout<<"it was here!"; 
        Tile temp;
        x[i]=atoi(str.c_str());
        switch(i){
            case 0: temp.set_idx(x[i]); temp.select(x[i]); break;
            case 1: temp.set_x(x[i]); break;
            case 2: temp.set_y(x[i]); break;
        }
        i++;
        if (i>2) {
            std::cout<<"haho";
            std::cout<<vecmax;
            i=0;
            vec[vecmax]=temp;
            vecmax++;
        }
    }
	in.close();
	
    bacaFileMonster();
}

void printMaps(SDL_Surface* &screen, int posX){
    int i=0;
    while(i<vecmax){
        vec[i].drawSprite(screen,posX);
        i++;
    }
}

void geser(){
    int i=0;
    while(i<vecmax){
        vec[i].set_x(vec[i].get_x());
        i++;
    }
}


