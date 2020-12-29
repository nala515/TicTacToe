#ifndef OPPONENT_H
#define OPPONENT_H

#include "GameArea.h"

class Opponent
{
    public:
        Opponent();
        virtual ~Opponent();

        void takeTurn(GameArea* gameArea, int &row, int &col);

    protected:

    private:
};

#endif // OPPONENT_H
