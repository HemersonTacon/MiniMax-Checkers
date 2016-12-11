#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>


class Piece
{
    public:
        Piece(int x, int y, int color, int type);
        ~Piece();

        int GetX() { return x; }
        void SetX(int val) { x = val; }
        int GetY() { return y; }
        void SetY(int val) { y = val; }
        int Getcolor() { return color; }
        void Setcolor(int val) { color = val; }
        int Gettype() { return type; }
        void Settype(int val) { type = val; }
        void print();

    protected:

    private:
        int x;
        int y;
        int color;
        int type;
};

#endif // PIECE_H
