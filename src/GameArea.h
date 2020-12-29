#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "Settings.h"

#include <wx/statline.h>

class GameArea
{
    public:
        GameArea();
        virtual ~GameArea();

        void setUp();
        void tearDown();
        void clearBoard();
        bool checkForWin();

    protected:

    private:
        // basic structure for each square
        struct box_t
        {
           wxPoint start;
           wxPoint stop;
           wxButton button;
        };

        Settings* mSettings;
        wxStaticLine *mLine;
        box_t *mBoxes[];
};

#endif // GAMEAREA_H
