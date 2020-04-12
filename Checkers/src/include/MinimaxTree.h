#ifndef MINIMAXTREE_H
#define MINIMAXTREE_H
#include "Node.h"
#include "Move.h"
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

//class Node;

class MinimaxTree {

    public:

        MinimaxTree(int depth, int heuristic);
        virtual ~MinimaxTree();

        int Getdepth() {

            return depth;
        }

        void Setdepth(int val) {

            depth = val;
        }

        Move GetbestMove() {

            return bestMove;
        }

        void SetbestMove(Move val) {

            bestMove = val;
        }

        int searchMiniMax(Node root);

        void AIMove(Node* board);

    protected:

        Node doTheMove(Node board, Move m);
        Node* doTheMoveForReal(Node* board, Move m);

    private:

        int depth;

        int boardValue[32];

        Move bestMove;
};

#endif // MINIMAXTREE_H
