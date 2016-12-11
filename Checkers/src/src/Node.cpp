#include "Node.h"

Node::Node(int n)
{
    aux->init_tree(this);
    this->Setn_child(n);
    children = new Node*[this->Getn_child()];
}
void Node::Highlight(int x, int y)
{
    Piece* p = this->Getboard(int(x/SIDE), int(y/SIDE));

    if(/*p->Getcolor() == WHITE &&*/ p->Gettype() != EMPTY && !pSelected){
        highlight = true;
        squareX = int(x/SIDE)*SIDE;
        squareY = int(y/SIDE)*SIDE;
    } else{
        highlight = false;
    }
}

void Node::SelectPiece(int button, int state, int x, int y){

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(highlight){
            pSelected = true;
            //printf("Selecionando %i, %i",squareX/SIDE, squareY/SIDE);
            pieceSelected = this->Getboard(squareX/SIDE, squareY/SIDE);
            this->Getmoves(pieceSelected);
        } else{
            pSelected = false;
            moves.clear();
        }
    }
}

void Node::MovePiece(int button, int state, int x, int y){
    if(pSelected){
        for(auto iter = moves.begin(); iter!= moves.end(); ++iter){
                Move m = *iter;
                /**se cliquei em um quadrado que está na lista de movimentos*/
                if(m.Getx() == int(x/SIDE) && m.Gety() == int(y/SIDE)){
                        Piece* destiny = this->Getboard(int(x/SIDE), int(y/SIDE));
                        int type = pieceSelected->Gettype();
                        int color = pieceSelected->Getcolor();
                        destiny->Settype(type);
                        destiny->Setcolor(color);
                        pieceSelected->Settype(EMPTY);
                        pieceSelected->Setcolor(0);
                        pSelected = false;
                        /**se este movimento é de ataque*/
                        if(m.Getatck() > 0){
                            std::list<Piece*> pAttacked = m.getAttacked();
                            /**Percorro a lista de peças atacadas e as removo do jogo*/
                            for(auto iter2 = pAttacked.begin(); iter2!= pAttacked.end(); ++iter2){
                                Piece* pRemove = *iter2;
                                pRemove->Settype(EMPTY);
                                pRemove->Setcolor(0);
                            }
                        }
                }
        }
    }
}


void Node::draw_circle(float radius, int posx, int posy){

    float theta = 2 * 3.1415926 / float(CIRCLE_PRECISION);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = radius;//we start at angle = 0

	float y = 0;

	glBegin(GL_POLYGON);
        for(int i = 0; i < CIRCLE_PRECISION; i++)
        {
            glVertex2f(x + posx, y + posy);//output vertex
            //calculate the tangential vector
            //remember, the radial vector is (x, y)
            //to get the tangential vector we flip those coordinates and negate one of them
            float tx = -y;
            float ty = x;
            //add the tangential vector
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            //correct using the radial factor
            x *= radial_factor;
            y *= radial_factor;
        }
	glEnd();

}

void Node::display(){

    /**Draw the inner squares of the board*/
    glLineWidth(3);
    glColor3f (0.2, 0.2, 0.2);
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
                if((i + j) % 2 == 1){
                    glBegin(GL_QUADS);
                        glVertex2f(i*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, (j+1)*SIDE);
                        glVertex2f(i*SIDE, (j+1)*SIDE);
                    glEnd();
                }
        }
    }

    /**Draw the outer square of the board*/
    glLineWidth(5);
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
                glVertex2f(0.0, 0.0);
                glVertex2f(WIDTH, 0.0);
                glVertex2f(WIDTH, HEIGHT);
                glVertex2f(0.0, HEIGHT);
    glEnd();

    /**Draw pieces*/
    glLineWidth(1);
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
                if((i + j) % 2 == 1){
                        Piece* p = this->Getboard(i, j);
                        if(p->Gettype() != EMPTY){
                            if(p->Getcolor() == WHITE){
                                glColor3f (0.8, 0.8, 0.8);
                            }else{
                                glColor3f (0.1, 0.1, 0.1);
                            }

                            draw_circle(25, (i+0.5)*SIDE, (j+0.5)*SIDE);

                            if(p->Gettype() == QUEEN){
                                glColor3f (0.5, 0.0, 0.0);
                                draw_circle(5, (i+0.5)*SIDE, (j+0.5)*SIDE);
                            }
                        }
                }
        }
    }
    if(highlight){
        aux->highlightSquare(squareX, squareY);
    }
    if(pSelected){
        aux->selectedSquare(squareX, squareY);
        aux->highlightMoves(moves);
    }


    glutPostRedisplay();
}

void Node::Getmoves(Piece* p)
{
    int x = p->GetX(), y = p->GetY();
    int type = p->Gettype(), color = p->Getcolor();
    Piece* temp;

    /**Checking simple movements ahead*/
    if(this->Getboard(x - 1, y + color)->Gettype() == EMPTY){
        moves.push_front(Move(x - 1 ,y + color, 0));
    }
    if(this->Getboard(x + 1, y + color)->Gettype() == EMPTY){
        moves.push_front(Move(x + 1 ,y + color, 0));
    }

    /**Checking simple atck moves*/
    if(this->Getboard(x - 1, y + color)->Getcolor() == -color && this->Getboard(x - 2, y + 2*color)->Gettype() == EMPTY){
        Move m = Move(x - 2 ,y + 2*color, 1);
        m.addAtck(this->Getboard(x - 1, y + color));
        moves.push_front(m);

    }
    if(this->Getboard(x + 1, y + color)->Getcolor() == -color && this->Getboard(x + 2, y + 2*color)->Gettype() == EMPTY){
        Move m = Move(x + 2 ,y + 2*color, 1);
        m.addAtck(this->Getboard(x + 1, y + color));
        moves.push_front(m);
    }
    if(this->Getboard(x - 1, y - color)->Getcolor() == -color && this->Getboard(x - 2, y - 2*color)->Gettype() == EMPTY){
        Move m = Move(x - 2 ,y - 2*color, 1);
        m.addAtck(this->Getboard(x - 1, y - color));
        moves.push_front(m);
    }
    if(this->Getboard(x + 1, y - color)->Getcolor() == -color && this->Getboard(x + 2, y - 2*color)->Gettype() == EMPTY){
        Move m = Move(x + 2 ,y - 2*color, 1);
        m.addAtck(this->Getboard(x + 1, y - color));
        moves.push_front(m);
    }

}

Node::~Node()
{
    //dtor
}
