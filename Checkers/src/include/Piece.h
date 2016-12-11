#ifndef PIECE_H
#define PIECE_H


class Piece
{
    public:
        Piece(int color, int type);
        ~Piece();

        int Getcolor() { return color; }
        void Setcolor(int val) { color = val; }
        int Gettype() { return type; }
        void Settype(int val) { type = val; }

    protected:

    private:
        int color;
        int type;
};

#endif // PIECE_H
