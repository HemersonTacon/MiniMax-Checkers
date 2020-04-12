#ifndef MISC_H
#define MISC_H

#define BLACK 1
#define WHITE -1
#define SIMPLE 1
#define QUEEN 3
#define OUT 0
#define EMPTY 2
#define WIDTH 560
#define HEIGHT 560
#define SIDE 70
#define CIRCLE_PRECISION 180

#include "Node.h"
#include "Move.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

class Node;

class misc
{
    public:
        misc();
        ~misc();

        void init_tree(Node* tree);
        void highlightSquare(int x, int y);
        void highlightMoves(int x, int y, std::list<Move> moves);
        void selectedSquare(int x, int y);

    protected:

    private:

};

#endif // MISC_H

