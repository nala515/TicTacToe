#include "Opponent.h"

Opponent::Opponent()
{
    //ctor
}

Opponent::~Opponent()
{
    //dtor
}

void Opponent::takeTurn(Settings::box_t** boxInfo, int &row, int &col)
{
    for(int i = 0; i < Settings::getInstance()->GetNumRows(); i++)
    {
        for(int j = 0; j < Settings::getInstance()->GetNumCols(); j++)
        {
            if(boxInfo[i][j].button->GetLabel() == "")
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}
