#ifndef NODE_H
#define NODE_H

#include "Piece.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <stdio.h>
#include "misc.h"
#include "move.h"
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

class misc;

class Node
{
    public:
        Node(int n);
        virtual ~Node();

        int Getturn() { return turn; }
        void Setturn(int val) {
            turn = val;
            moves.clear();
            this->GetAllmoves(val);
            }
        int Getn_child() { return num_child; }
        void Setn_child(int val) { num_child = val; }
        Node* Getparent() { return parent; }
        void Setparent(Node* val) { parent = val; }
        Node** Getchildren() { return children; }
        void Setchildren(Node** val) { children = val; }
        void SetPiece(Piece* p);
        Piece* GetPiece(int x, int y);
        bool RemovePiece(Piece* p);
        int Getmoves(Piece* p);
        void GetAllmoves(int color);
        void draw_circle(float radius, int posx, int posy);
        void display();
        void Highlight(int x, int y);
        void SelectPiece(int button, int state, int x, int y);
        void MovePiece(int button, int state, int x, int y);


    protected:
        bool highlight = false, pSelected = false, moving = false;
        int squareX = -SIDE, squareY = -SIDE;
        Piece* pieceSelected;
        std::list<Move> moves;
        misc* aux;

    private:

        int turn;
        int num_child;
        Node* parent;
        Node** children;
        std::list<Piece*> Pieces[2];
        int pieceCounter[2];


        int AtckMoves(int color, int type, Move origin);
};

#endif // NODE_H
