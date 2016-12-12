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
        void Setturn(int val) { turn = val; }
        int Getn_child() { return num_child; }
        void Setn_child(int val) { num_child = val; }
        Node* Getparent() { return parent; }
        void Setparent(Node* val) { parent = val; }
        Node** Getchildren() { return children; }
        void Setchildren(Node** val) { children = val; }
        Piece* Getboard(int x, int y) {
            if(0 <= x && x < 8 && 0 <= y && y < 8){
                return this->board[x][y];
            }
            else{
                Piece* p = new Piece(-1, -1, 0, OUT); //Peça fora do tabuleiro
                return p;
            }

        }
        void Setboard(int x, int y, Piece* p) { this->board[x][y] = p; }
        void Getmoves(Piece* p);
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
        Piece* board[8][8];
        Node* parent;
        Node** children;


        int AtckMoves(int color, int type, Move origin);
};

#endif // NODE_H
