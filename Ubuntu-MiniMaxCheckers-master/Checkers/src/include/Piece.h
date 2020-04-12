#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include<iostream>


class Piece
{
    public:
        Piece(int x, int y, int color, int type);
        ~Piece();

        int GetX() { return x; }
        void SetX(int val) {
            //this->print();
            //std::cout<<" ***Changing X to "<<val;
            x = val; }
        int GetY() { return y; }
        void SetY(int val) {
            //this->print();
            //std::cout<<" ***Changing Y to "<<val;
            y = val; }
        int Getcolor() { return color; }
        void Setcolor(int val) {
            //this->print();
            //std::cout<<" ***Changing color to "<<val;
            color = val; }
        int Gettype() { return type; }
        void Settype(int val) {
            //this->print();
            //std::cout<<" ***Changing type to "<<val;
            type = val; }
        void print();

    protected:

    private:
        int x;
        int y;
        int color;
        int type;
};

#endif // PIECE_H
