#define BLACK 1
#define WHITE -1
#define SIMPLE 1
#define QUEEN 3

#include "Node.h"
#include <iostream>


Node* init_tree(){

    Node* tree = new Node(7);

    for(int j = 0; j < 8; ++j){
        for(int i = 0; i<3; ++i){
            if((j + i) % 2 == 1){
                tree->Setboard(j, i, new Piece(BLACK, QUEEN));
            } else{
                tree->Setboard(j, i, NULL);
            }
        }
        tree->Setboard(j, 3, NULL);
        tree->Setboard(j, 4, NULL);
        for(int i = 5; i<8; ++i){
            if((j + i) % 2 == 1){
                tree->Setboard(j, i, new Piece(WHITE, QUEEN));
            } else{
                tree->Setboard(j, i, NULL);
            }
        }
    }
    tree->Setturn(WHITE);
    tree->Setparent(NULL);

    return tree;
}
