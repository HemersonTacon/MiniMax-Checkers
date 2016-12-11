#include "Move.h"

Move::Move(int x, int y, int atck)
{
    this->Setx(x);
    this->Sety(y);
    this->Setatck(atck);
}

void Move::addAtck(Piece* p){
    attacked.push_back(p);
}

void Move::clearAtck(){
    attacked.clear();
}

std::list<Piece*> Move::getAttacked(){
    return attacked;
}

Move::~Move()
{
    //dtor
}
