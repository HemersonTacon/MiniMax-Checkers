#include "MinimaxTree.h"

MinimaxTree::MinimaxTree(int depth, int heuristic){

    this->Setdepth(depth);

    //ctor
    int bValue[2][32] ={{  4,  4,  4,  4,
                         4,  3,  3,  3,
                           3,  2,  2,  4,
                         4,  2,  1,  3,
                           3,  1,  2,  4,
                         4,  2,  2,  3,
                           3,  3,  3,  4,
                         4,  4,  4,  4   },

                        {  4,  4,  4,  4,
                         4,  3,  3,  3,
                           3,  2,  2,  4,
                         4,  2,  3,  3,
                           3,  3,  2,  4,
                         4,  2,  2,  3,
                           3,  3,  3,  4,
                         4,  4,  4,  4   }};

    memcpy(boardValue, bValue[heuristic % 2], sizeof(boardValue));
}

void MinimaxTree::AIMove(Node* board) {

    std::list<Piece> bkp[2];
    int bkpTurn = board->Getturn(), bkpDepth = board->Getdepth(), bkpAlfa = board->Getalfa(), bkpBeta = board->Getbeta();
    board->makeBkp(bkp);

    this->searchMiniMax(*board);

    board->restoreBkp(bkp);
    board->Setturn(bkpTurn);
    board->Setdepth(bkpDepth);
    board->Setalfa(bkpAlfa);
    board->Setbeta(bkpBeta);

    board = this->doTheMoveForReal(board, this->GetbestMove());
}

int MinimaxTree::searchMiniMax(Node root) {

    if (root.Getdepth() == this->Getdepth()) {

        std::list<Piece*>* Pieces = root.GetAllPieces();
        int totalValue = 0;

        if (Pieces[0].begin() == Pieces[0].end()) {

            return INT_MAX;
        } else if (Pieces[1].begin() == Pieces[1].end()) {

            return INT_MIN;
        }

        for (int i = 0; i < 2; ++i) {
            for (auto iter = Pieces[i].begin(); iter!= Pieces[i].end(); ++iter) {

                Piece* p = *iter;
                int value = p->Gettype();

                /** Se estiver a um movimento de se tornar dama */
                if (value == SIMPLE && int(p->Getcolor()*2.5 + 3.5) == p->GetY()) {

                    value += 2;
                }

                //conversão dos valores de matriz para vetor
                totalValue += p->Getcolor() * (value * boardValue[int(((p->GetX() + 1) * (p->GetY() + 1))/2)]);
            }
        }

        return totalValue; //value of board

    } else {

        int value;
        std::list<Move> moves = root.GetAllmoves();

        for (auto it = moves.begin(); it!= moves.end(); ++it) {

            std::list<Piece> bkp[2];
            int bkpTurn = root.Getturn(), bkpDepth = root.Getdepth(), bkpAlfa = root.Getalfa(), bkpBeta = root.Getbeta();
            root.makeBkp(bkp);

            value = searchMiniMax(this->doTheMove(root, *it));

            root.restoreBkp(bkp);
            root.Setturn(bkpTurn);
            root.Setdepth(bkpDepth);
            root.Setalfa(bkpAlfa);
            root.Setbeta(bkpBeta);

            if (root.Getturn() == BLACK && value > root.Getalfa()) {

                root.Setalfa(value);

                if (root.Getdepth() == 0) {

                    this->SetbestMove(*it);
                }
            } else if (root.Getturn() == WHITE && value < root.Getbeta()) {

                root.Setbeta(value);
            }

            if (root.Getbeta() <= root.Getalfa()) {

                it = moves.end();
                --it;
            }
        }

        if (root.Getturn() == BLACK) {

            return root.Getalfa();
        } else if (root.Getturn() == WHITE) {

            return root.Getbeta();
        }
    }
}

Node MinimaxTree::doTheMove(Node board, Move m) {

    Piece* destiny = *(m.getDestinies().begin());
    Piece* pieceSelected = board.GetPiece(m.Getx(), m.Gety());
    pieceSelected->SetX(destiny->GetX());
    pieceSelected->SetY(destiny->GetY());

    if (m.Getatck() > 0) {

        Piece* pRemove = *(m.getAttacked().begin());
        board.RemovePiece(pRemove);

        /** Se é um ataque em cadeia */
        if (m.Getatck() > 1) {

            board.Setturn(board.Getturn());

            /** Por se tratar de estar no meio de um ataque em cadeia, apenas um movimento será gerado */
            m = *((board.GetAllmoves()).begin());

            return doTheMove(board, m);
        }
    }

    if (pieceSelected->GetY() == 3.5*(1 + pieceSelected->Getcolor())) {

        pieceSelected->Settype(QUEEN);
    }

    board.Setturn(-board.Getturn());
    board.Setdepth(board.Getdepth()+1);

    return board;
}

Node* MinimaxTree::doTheMoveForReal(Node* board, Move m) {

    m.print();
    Piece* destiny = *(m.getDestinies().begin());
    Piece* pieceSelected = board->GetPiece(m.Getx(), m.Gety());
    pieceSelected->SetX(destiny->GetX());
    pieceSelected->SetY(destiny->GetY());

    if (m.Getatck() > 0) {

        Piece* pRemove = *(m.getAttacked().begin());
        pRemove = board->GetPiece(pRemove->GetX(), pRemove->GetY());

        if (board->RemovePiece(pRemove)) {

            std::cout<<"\nRemovida peça ";
        }else{

            std::cout<<"\nFalha ao remover peça ";
        }

        pRemove->print();

        /** Se é um ataque em cadeia */
        if (m.Getatck() > 1) {

            board->Setturn(board->Getturn());

            /** Por se tratar de estar no meio de um ataque em cadeia, apenas um movimento será gerado */
            m = *((board->GetAllmoves()).begin());

            return doTheMoveForReal(board, m);
        }
    }

    if (pieceSelected->GetY() == 3.5*(1 + pieceSelected->Getcolor())) {

        pieceSelected->Settype(QUEEN);
    }

    board->Setturn(-board->Getturn());

    return board;
}

MinimaxTree::~MinimaxTree() {
    //dtor
}
