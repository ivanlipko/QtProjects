#include "game.h"

unsigned short gamePoints_;

void gAdd(unsigned short points){
    gamePoints_ += points;
    return;
}

void gRemove(unsigned short points){
    gamePoints_ -= points;
    return;
}

bool gIs50(){
    return gamePoints_ == 50;
}

unsigned short gGetPoints(){
    return gamePoints_;
}
