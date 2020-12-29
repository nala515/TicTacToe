#ifndef OPPONENT_H
#define OPPONENT_H

#include "Settings.h"

class Opponent
{
    public:
        Opponent();
        virtual ~Opponent();

        void takeTurn(Settings::box_t** boxInfo, int &row, int &col);

    protected:

    private:
};

#endif // OPPONENT_H
