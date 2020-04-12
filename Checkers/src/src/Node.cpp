#include "Node.h"

Node::Node() {

    aux->init_tree(this);
    pieceCounter[0] = 0;
    pieceCounter[1] = 0;
    alfa = INT_MIN;
    beta = INT_MAX;
    depth = 0;
}

void Node::SetPiece(Piece* p) {

    /**Gives me 1 when color == BLACK and 0 when color == WHITE*/
    this->Pieces[int(0.5 * (p->Getcolor() + 1))].push_back(p);
    ++pieceCounter[int(0.5 * (p->Getcolor() + 1))];
}

Piece* Node::GetPiece(int x, int y) {

    if (x < 0 || 7 < x || y < 0 || 7 < y) {

        return (new Piece(-1, -1, 0, OUT)); //Peça fora do tabuleiro
    } else {

        for (int i = 0; i < 2; ++i) {

            for (auto iter = Pieces[i].begin(); iter!= Pieces[i].end(); ++iter){

                if ((*iter)->GetX() == x && (*iter)->GetY() == y) {

                    return *iter;
                }
            }
        }
    }

    return (new Piece(x, y, 0, EMPTY));
}

bool Node::RemovePiece(Piece* p) {

    for (int i = 0; i < 2; ++i) {

        auto it = std::find(Pieces[i].begin(), Pieces[i].end(), p);

        if (it!= Pieces[i].end()) {

            //std::cout<<"\nRemoving piece...\n";
            //(*it)->print();
            Pieces[i].erase(it);
            --pieceCounter[i];
            return true;
        }
    }

    return false;
}

void Node::Highlight(int x, int y) {

    Piece* p = this->GetPiece(int(x/SIDE), int(y/SIDE));

    if (p->Getcolor() == turn && p->Gettype() != EMPTY && !pSelected) {

        highlight = true;
        squareX = int(x/SIDE)*SIDE;
        squareY = int(y/SIDE)*SIDE;
    } else if (!moving) {

        highlight = false;
    }
}

void Node::SelectPiece(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !moving) {

        if (highlight) {

            pSelected = true;
            pieceSelected = this->GetPiece(squareX/SIDE, squareY/SIDE);
        } else {

            pSelected = false;
            //moves.clear();
        }
    }
}

void Node::MovePiece(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (pSelected) {

            for (auto iter = moves.begin(); iter!= moves.end(); ++iter) {

                    Move m = *iter;

                    /** se o movimento pertence à peça selecionada */
                    if (m.Getx() == pieceSelected->GetX() && m.Gety() == pieceSelected->GetY()) {

                        Piece* destiny = *(m.getDestinies().begin());

                        //std::cout<<"\nThe ove from "<<m.Getx()<<", "<<m.Gety()<<" to "<<destiny->GetX()<<", "<<destiny->GetY();
                        //std::cout<<"\nBelongs to piece "<<pieceSelected->GetX()<<", "<<pieceSelected->GetY()<<" with color "<<pieceSelected->Getcolor();

                        /** se cliquei em um quadrado que está na lista de movimentos */
                        if (destiny->GetX() == int(x/SIDE) && destiny->GetY()  == int(y/SIDE)) {

                                pieceSelected->SetX(destiny->GetX());
                                pieceSelected->SetY(destiny->GetY());

                                /** se este movimento é de ataque */
                                if (m.Getatck() > 0) {

                                    Piece* pRemove = *(m.getAttacked().begin());
                                    this->RemovePiece(pRemove);

                                    /** Se é um ataque em cadeia */
                                    if (m.Getatck() > 1) {

                                        pSelected = true;
                                        moving = true;
                                        squareX = pieceSelected->GetX()*SIDE;
                                        squareY = pieceSelected->GetY()*SIDE;
                                        this->Setturn(this->Getturn());
                                        return;
                                    }
                                }

                                if (pieceSelected->GetY() == 3.5*(1 + pieceSelected->Getcolor())) {

                                    pieceSelected->Settype(QUEEN);
                                }

                                this->Setturn(-this->Getturn());
                                moving = false;
                                iter = moves.end();
                                iter--;
                        }
                    }

            }

            if (!moving) {

                pSelected = false;
                //moves.clear();
            }

        }
    }
}

void Node::draw_circle(float radius, int posx, int posy) {

    float theta = 2 * 3.1415926 / float(CIRCLE_PRECISION);
    float tangetial_factor = tanf(theta); // calculate the tangential factor
    float radial_factor = cosf(theta); // calculate the radial factor
    float x = radius; // we start at angle = 0
    float y = 0;

    glBegin(GL_POLYGON);

        for (int i = 0; i < CIRCLE_PRECISION; i++) {

            glVertex2f(x + posx, y + posy); // output vertex

            // calculate the tangential vector
            // remember, the radial vector is (x, y)
            // to get the tangential vector we flip those coordinates and negate one of them
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

void Node::display() {

    /** Draw the inner squares of the board */
    glLineWidth(3);
    glColor3f (0.2, 0.2, 0.2);

    for (int i = 0; i < 8; ++i) {

        for (int j = 0; j < 8; ++j) {

                if ((i + j) % 2 == 1) {

                    glBegin(GL_QUADS);
                        glVertex2f(i*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, (j+1)*SIDE);
                        glVertex2f(i*SIDE, (j+1)*SIDE);
                    glEnd();
                }
        }
    }

    /** Draw the outer square of the board */
    glLineWidth(5);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0, 0.0);
        glVertex2f(WIDTH, 0.0);
        glVertex2f(WIDTH, HEIGHT);
        glVertex2f(0.0, HEIGHT);
    glEnd();

    /** Draw pieces */
    glLineWidth(1);

    for (int i = 0; i < 2; ++i) {
        for (auto iter = Pieces[i].begin(); iter!= Pieces[i].end(); ++iter) {

            Piece* p = *iter;
            int x = p->GetX(), y = p->GetY();
            glColor3f(i * (-0.7) + 0.8, i * (-0.7) + 0.8, i * (-0.7) + 0.8);
            draw_circle(25, (x+0.5)*SIDE, (y+0.5)*SIDE);

            if (p->Gettype() == QUEEN) {

                glColor3f(0.5, 0.0, 0.0);
                draw_circle(5, (x + 0.5) * SIDE, (y + 0.5) * SIDE);
            }
        }
    }

    if (highlight) {

        aux->highlightSquare(squareX, squareY);
    }

    if (pSelected) {

        aux->selectedSquare(squareX, squareY);
        aux->highlightMoves(pieceSelected->GetX(), pieceSelected->GetY(), moves);
    }

    glutPostRedisplay();
}

void Node::GetAllmoves(int color) {

    if (color != WHITE && color != BLACK) {

        std::cout<<"\nInvalid color on \"void Node::GetAllmoves(int color)\"\n";
    }
    else {

        int chains[12] = {0}, i = 0, maxChain;

        for (auto iter = Pieces[int(0.5 * (color + 1))].begin(); iter!= Pieces[int(0.5 * (color + 1))].end(); ++iter) {

            chains[i] = this->Getmoves(*iter);
            ++i;
        }

        auto minmax = std::minmax_element(std::begin(chains), std::end(chains));
        maxChain = *minmax.second;

        //std::cout<<"\n\n###\n\nAll Max chain "<<maxChain;
        for (auto iter = moves.begin(); iter!= moves.end(); ) {

            Move m = (*iter);
            Piece* dest = *(m.getDestinies().begin());

            //std::cout<<"\nMove from "<<m.Getx()<<", "<<m.Gety()<<" to "<<dest->GetX()<<", "<<dest->GetY()<<" with chain "<<(*iter).Getatck();
            if ((*iter).Getatck() < maxChain) {

                //std::cout<<"\nErasing that...";
                iter = moves.erase(iter);
            } else {

                ++iter;
            }
        }
    }
}

int Node::Getmoves(Piece* p) {

    int x = p->GetX(), y = p->GetY(), maxChain;
    int type = p->Gettype(), color = p->Getcolor();
    Piece* destiny = this->GetPiece(x - 1, y + color);

    /** Checking simple movements ahead */

    if (destiny->Gettype() == EMPTY) {

        Move m = Move(x, y, 0);
        m.addDst(destiny);

        //m.print();
        moves.push_front(m);
    }

    destiny = this->GetPiece(x + 1, y + color);

    if (destiny->Gettype() == EMPTY) {

        Move m = Move(x, y, 0);
        m.addDst(destiny);

        //m.print();
        moves.push_front(m);
    }
    if (type == QUEEN) {

        destiny = this->GetPiece(x - 1, y - color);

        if (destiny->Gettype() == EMPTY) {

            Move m = Move(x, y, 0);
            m.addDst(destiny);
            //m.print();
            moves.push_front(m);
        }

        destiny = this->GetPiece(x + 1, y - color);

        if (destiny->Gettype() == EMPTY) {

            Move m = Move(x, y, 0);
            m.addDst(destiny);

            //m.print();
            moves.push_front(m);
        }
    }

    /** Checking atck moves */
    maxChain = this->AtckMoves(color, type, Move(x , y, 0));

    //std::cout<<"\n\n\n***Max chain "<<maxChain<<" from piece";
    //p->print();

    /** Para obedecer a lei da maioria, elimino todos movimentos com menos capturas

    for (auto iter = moves.begin(); iter!= moves.end(); ) {

        Move m = (*iter);
        Piece* dest = *(m.getDestinies().begin());

        //std::cout<<"\nTesting move from "<<m.Getx()<<", "<<m.Gety()<<" to "<<dest->GetX()<<", "<<dest->GetY()<<" with chain "<<(*iter).Getatck();

        if ((*iter).Getatck() < maxChain) {

            //std::cout<<"\nErasing that...";
            iter = moves.erase(iter);
        } else {

            ++iter;
        }
    }
    */

    return maxChain;
}

int Node::AtckMoves(int color, int type, Move origin) {

    int x, y;
    int chain = origin.Getatck();
    int chainDegree[4] = {chain, chain, chain, chain};
    std::list<Piece*> pAttacked = origin.getAttacked();
    std::list<Piece*> pDestinies = origin.getDestinies();

    if (chain == 0) {

        //Se ainda não partir de uma chain, o lugar onde procuro movimentos é a origem do movimento
        x = origin.Getx();
        y = origin.Gety();
    } else {

        //Senão, eu tenho que partir do último destino na lista
        auto it = origin.getDestinies().end();
        --it;
        Piece* destiny = *it;
        x = destiny->GetX();
        y = destiny->GetY();
    }

    for (int i = 0; i<4; ++i) {

        int xSignal = (int(i/2))*2 - 1, /** Gives me -1,-1, 1, 1 */
            ySignal = (int(i%2))*2 - 1; /** Gives me -1, 1,-1, 1 */

        Piece* attacked = this->GetPiece(x + xSignal, y + ySignal*color);
        Piece* destiny = this->GetPiece(x + 2*xSignal, y + 2*ySignal*color);

        if (attacked->Getcolor() == -color && destiny->Gettype() == EMPTY
           && std::find(pAttacked.begin(), pAttacked.end(), attacked) == pAttacked.end()) {

            Move m = Move(origin.Getx(), origin.Gety(), chain + 1);

            for (auto iter = pAttacked.begin(); iter!= pAttacked.end(); ++iter) {

                m.addAtck(*iter);
            }

            for( auto iter = pDestinies.begin(); iter!= pDestinies.end(); ++iter) {

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

void Node::makeBkp(std::list<Piece>* bkpPieces) {

    for (int i = 0; i < 2; ++i) {

        for (auto iter = Pieces[i].begin(); iter!= Pieces[i].end(); ++iter) {

            Piece* p = *iter;
            bkpPieces[i].push_back(*p);
        }
    }
}

void Node::restoreBkp(std::list<Piece>* bkpPieces){
    Pieces[0].clear();
    Pieces[1].clear();
    for(int i = 0; i < 2; ++i){
        for(auto iter = bkpPieces[i].begin(); iter!= bkpPieces[i].end(); ++iter){
            Piece p = *iter;
            Pieces[i].push_back(new Piece(p.GetX(), p.GetY(), p.Getcolor(), p.Gettype()));
        }
    }
}

Node::~Node()
{
    //dtor
}
