#include "../include/Move.h"

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

void Move::addDst(Piece* p){
    destinies.push_back(p);
}

void Move::clearDst(){
    destinies.clear();
}

std::list<Piece*> Move::getDestinies(){
    return destinies;
}


void Move::print(){
    std::cout<<"\nAtcks "<<this->Getatck()<<" X: "<<this->Getx()<<", Y: "<<this->Gety();
}

Move::~Move()
{
    //dtor
}
