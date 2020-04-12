#include "Piece.h"

Piece::Piece(int x, int y, int color, int type)
{
    this->SetX(x);
    this->SetY(y);
    this->Setcolor(color);
    this->Settype(type);
}


void Piece::print(){
    printf("\nX: %d, Y: %d, Color: %d, Type: %d", this->GetX(), this->GetY(), this->Getcolor(), this->Gettype());
}
Piece::~Piece()
{
    //dtor
}
