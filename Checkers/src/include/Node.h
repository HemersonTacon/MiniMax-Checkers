#ifndef NODE_H
#define NODE_H

#include "Piece.h"


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
        Piece* Getboard(int x, int y) { return this->board[x][y]; }
        void Setboard(int x, int y, Piece* p) { this->board[x][y] = p; }

        void draw_circle(float radius, int posx, int posy);
        void display();


    protected:

    private:
        int turn;
        int num_child;
        Piece* board[8][8];
        Node* parent;
        Node** children;
};

#endif // NODE_H
