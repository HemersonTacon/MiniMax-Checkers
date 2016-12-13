#ifndef NODE_H
#define NODE_H

#include "Piece.h"
#include <limits>
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
#define SIMPLE 5
#define QUEEN 10
#define OUT 0
#define EMPTY 2
#define WIDTH 560
#define HEIGHT 560
#define SIDE 70
#define CIRCLE_PRECISION 180

class misc;
class MinimaxTree;

class Node
{
    public:
        Node();
        virtual ~Node();

        int Getturn() { return turn; }
        void Setturn(int val) {
            turn = val;
            moves.clear();
            this->GetAllmoves(val);
            }
        void SetPiece(Piece* p);
        Piece* GetPiece(int x, int y);
        bool RemovePiece(Piece* p);
        std::list<Piece*>* GetAllPieces(){ return Pieces;}
        int Getmoves(Piece* p);
        void GetAllmoves(int color);
        void draw_circle(float radius, int posx, int posy);
        void display();
        void Highlight(int x, int y);
        void SelectPiece(int button, int state, int x, int y);
        void MovePiece(int button, int state, int x, int y);
        int Getalfa(){return alfa;}
        void Setalfa(int val){alfa = val;}
        int Getbeta(){return beta;}
        void Setbeta(int val){beta = val;}
        int Getdepth(){return depth;}
        void Setdepth(int val){depth = val;}
        std::list<Move> GetAllmoves(){ return moves;}
        void makeBkp(std::list<Piece>* bkpPieces);
        void restoreBkp(std::list<Piece>* bkpPieces);

    protected:
        bool highlight = false, pSelected = false, moving = false;
        int squareX = -SIDE, squareY = -SIDE;
        Piece* pieceSelected;
        std::list<Move> moves;
        misc* aux;

    private:

        int turn;
        int num_child;
        std::list<Piece*> Pieces[2];
        int pieceCounter[2];
        int alfa;
        int beta;
        int depth;


        int AtckMoves(int color, int type, Move origin);
};

#endif // NODE_H
