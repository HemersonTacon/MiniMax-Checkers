#include <misc.h>


void misc::init_tree(Node* tree){

    for(int j = 0; j < 8; ++j){
        for(int i = 0; i<3; ++i){
            if((j + i) % 2 == 1){
                tree->Setboard(j, i, new Piece(j, i, BLACK, SIMPLE));
            } else{
                tree->Setboard(j, i, new Piece(j, i, 0, EMPTY));
            }
        }
        tree->Setboard(j, 3, new Piece(j, 3, 0, EMPTY));
        tree->Setboard(j, 4, new Piece(j, 4, 0, EMPTY));
        for(int i = 5; i<8; ++i){
            if((j + i) % 2 == 1){
                tree->Setboard(j, i, new Piece(j, i, WHITE, SIMPLE));
            } else{
                tree->Setboard(j, i, new Piece(j, i, 0, EMPTY));
            }
        }
    }
    tree->Setturn(WHITE);
    tree->Setparent(NULL);
}




void misc::highlightSquare(int x, int y){

    glLineWidth(2);
    for(int i = 0; i < 5; ++i){
        glColor3f(1.0f - 0.2*i, 1.0f - 0.2*i, 0.2f);
        glBegin(GL_LINE_LOOP);
            glVertex2i(x + i, y + i);
            glVertex2i(x +i, y + SIDE - i);
            glVertex2i(x + SIDE - i, y + SIDE - i);
            glVertex2i(x + SIDE - i, y + i);
        glEnd();
    }

    glutPostRedisplay();
}

void misc::selectedSquare(int x, int y){

    glLineWidth(2);
    for(int i = 0; i < 5; ++i){
        glColor3f(0.2f, 1.0f - 0.2*i, 1.0f - 0.2*i);
        glBegin(GL_LINE_LOOP);
            glVertex2i(x + i, y + i);
            glVertex2i(x +i, y + SIDE - i);
            glVertex2i(x + SIDE - i, y + SIDE - i);
            glVertex2i(x + SIDE - i, y + i);
        glEnd();
    }

    glutPostRedisplay();
}


void misc::highlightMoves(std::list<Move> moves){

    for(auto iter = moves.begin(); iter!= moves.end(); ++iter){
        Piece* p = *((*iter).getDestinies().begin());
        int x = p->GetX(), y = p->GetY();
        selectedSquare(x*SIDE, y*SIDE);
    }

}

misc::~misc()
{
    //dtor
}

