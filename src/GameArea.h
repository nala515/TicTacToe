#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "Settings.h"

#include <wx/statline.h>
#include "stdlib.h"

class GameArea
{
    public:
        GameArea(wxFrame *frame, int buttonId);
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
           wxButton *button;
        };

        wxFrame *mFrame;
        Settings *mSettings;
        int mButtonId;
        bool mGameActive;

        // graphics
        std::vector<wxStaticLine*> mLine;
        std::vector<std::vector<box_t*>> mBox;
};

#endif // GAMEAREA_H
