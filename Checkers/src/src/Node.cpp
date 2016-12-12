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

    if(p->Getcolor() == turn && p->Gettype() != EMPTY && !pSelected){
        highlight = true;
        squareX = int(x/SIDE)*SIDE;
        squareY = int(y/SIDE)*SIDE;
    } else if(!moving){
        highlight = false;
    }
}

void Node::SelectPiece(int button, int state, int x, int y){

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !moving){
        if(highlight){
            pSelected = true;
            pieceSelected = this->Getboard(squareX/SIDE, squareY/SIDE);
            this->Getmoves(pieceSelected);
        } else{
            pSelected = false;
            moves.clear();
        }
    }
}

void Node::MovePiece(int button, int state, int x, int y){

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(pSelected){
            for(auto iter = moves.begin(); iter!= moves.end(); ++iter){
                    Move m = *iter;
                    Piece* destiny = *(m.getDestinies().begin());
                    /**se cliquei em um quadrado que está na lista de movimentos*/
                    if(destiny->GetX() == int(x/SIDE) && destiny->GetY()  == int(y/SIDE)){
                            int type = pieceSelected->Gettype();
                            int color = pieceSelected->Getcolor();
                            destiny->Settype(type);
                            destiny->Setcolor(color);
                            pieceSelected->Settype(EMPTY);
                            pieceSelected->Setcolor(0);
                            /**se este movimento é de ataque*/
                            if(m.Getatck() > 0){
                                Piece* pRemove = *((*iter).getAttacked().begin());
                                pRemove->Settype(EMPTY);
                                pRemove->Setcolor(0);
                                /**Se é um ataque em cadeia*/
                                if(m.Getatck() > 1){
                                    pSelected = true;
                                    moving = true;
                                    pieceSelected = destiny;
                                    squareX = pieceSelected->GetX()*SIDE;
                                    squareY = pieceSelected->GetY()*SIDE;
                                    moves.clear();
                                    this->Getmoves(pieceSelected);
                                    return;
                                }
                            }
                            if(destiny->GetY() == 3.5*(1 + destiny->Getcolor())){
                                destiny->Settype(QUEEN);
                            }
                            turn = -turn;
                            moving = false;
                            iter = moves.end();
                            iter--;
                    }
            }
            if(!moving){
                pSelected = false;
                moves.clear();
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
    int x = p->GetX(), y = p->GetY(), maxChain;
    int type = p->Gettype(), color = p->Getcolor();
    Piece* destiny = this->Getboard(x - 1, y + color);
    /**Checking simple movements ahead*/

    if(destiny->Gettype() == EMPTY){
        Move m = Move(destiny->GetX(),destiny->GetY(), 0);
        m.addDst(destiny);
        //m.print();
        moves.push_front(m);
    }
    destiny = this->Getboard(x + 1, y + color);
    if(destiny->Gettype() == EMPTY){
        Move m = Move(destiny->GetX(),destiny->GetY(), 0);
        m.addDst(destiny);
        //m.print();
        moves.push_front(m);
    }
    if(type == QUEEN){
        destiny = this->Getboard(x - 1, y - color);
        if(destiny->Gettype() == EMPTY){
            Move m = Move(destiny->GetX(),destiny->GetY(), 0);
            m.addDst(destiny);
            //m.print();
            moves.push_front(m);
        }
        destiny = this->Getboard(x + 1, y - color);
        if(destiny->Gettype() == EMPTY){
            Move m = Move(destiny->GetX(),destiny->GetY(), 0);
            m.addDst(destiny);
            //m.print();
            moves.push_front(m);
        }
    }


    /**Checking atck moves*/
    maxChain = this->AtckMoves(color, type, Move(x , y, 0));
    //std::cout<<"\nMax chain "<<maxChain;
    /**Para obedecer a lei da maioria, elimino todos movimentos com menos capturas*/
    for(auto iter = moves.begin(); iter!= moves.end(); ){
        //std::cout<<"\nTesting move to "<<(*iter).Getx()<<", "<<(*iter).Gety()<<" with chain "<<(*iter).Getatck();
        if((*iter).Getatck() < maxChain){
            //std::cout<<"\nErasing that...";
            iter = moves.erase(iter);
        } else{
            ++iter;
        }
    }

}

int Node::AtckMoves(int color, int type, Move origin){

    int x = origin.Getx(), y = origin.Gety();
    int chain = origin.Getatck();
    int chainDegree[4] = {chain, chain, chain, chain};
    std::list<Piece*> pAttacked = origin.getAttacked();
    std::list<Piece*> pDestinies = origin.getDestinies();


    for(int i = 0; i<4; ++i){
        int xSignal = (int(i/2))*2 - 1, /**Gives me -1,-1, 1, 1*/
            ySignal = (int(i%2))*2 - 1; /**Gives me -1, 1,-1, 1*/

        Piece* attacked = this->Getboard(x + xSignal, y + ySignal*color);
        Piece* destiny = this->Getboard(x + 2*xSignal, y + 2*ySignal*color);

        if(attacked->Getcolor() == -color && destiny->Gettype() == EMPTY
           && std::find(pAttacked.begin(), pAttacked.end(), attacked) == pAttacked.end()){

            Move m = Move(destiny->GetX() , destiny->GetY(), chain + 1);
            for(auto iter = pAttacked.begin(); iter!= pAttacked.end(); ++iter){
                m.addAtck(*iter);
            }

            for(auto iter = pDestinies.begin(); iter!= pDestinies.end(); ++iter){
                m.addDst(*iter);
            }

            m.addAtck(attacked);
            m.addDst(destiny);
            //m.print();
            moves.push_front(m);
            chainDegree[i] = this->AtckMoves(color, type, m);
        }
    }

    auto minmax = std::minmax_element(std::begin(chainDegree), std::end(chainDegree));

    return *minmax.second;
}


Node::~Node()
{
    //dtor
}
