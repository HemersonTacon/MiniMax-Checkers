#ifndef MOVE_H
#define MOVE_H

#include <list>
#include "Piece.h"
#include <iostream>

class Move
{
    public:
        Move(int x, int y, int atck);
        Move(){}
        virtual ~Move();

        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }
        int Getatck() { return atck; }
        void Setatck(int val) { atck = val; }
        void addAtck(Piece* p);
        void clearAtck();
        std::list<Piece*> getAttacked();
        void addDst(Piece* p);
        void clearDst();
        std::list<Piece*> getDestinies();
        void print();

    protected:
        std::list<Piece*> attacked;
        std::list<Piece*> destinies;
    private:

        int x;
        int y;
        int atck;
};

#endif // MOVE_H
