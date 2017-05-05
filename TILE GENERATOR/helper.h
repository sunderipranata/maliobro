void apply_cropped_surface(int posX, int posY,  int cropW, int cropH, SDL_Surface *image, SDL_Surface *screen){
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












