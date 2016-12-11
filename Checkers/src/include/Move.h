#ifndef MOVE_H
#define MOVE_H

#include <list>
#include "Piece.h"

class Move
{
    public:
        Move(int x, int y, int atck);
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

    protected:
        std::list<Piece*> attacked;

    private:

        int x;
        int y;
        int atck;
};

#endif // MOVE_H
