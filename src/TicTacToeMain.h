/***************************************************************
 * Name:      TicTacToeMain.h
 * Purpose:   Defines Application Frame
 * Author:    Jacqueline Robinson ()
 * Created:   2020-12-19
 * Copyright: Jacqueline Robinson ()
 * License:
 **************************************************************/

#ifndef TICTACTOEMAIN_H
#define TICTACTOEMAIN_H

#include "Settings.h"
#include "Opponent.h"

#include <wx/button.h>
#include <wx/dcclient.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/wxprec.h>

class TicTacToeFrame: public wxFrame
{
    public:
        TicTacToeFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
        virtual ~TicTacToeFrame();

    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idNewGame,
            idButton
        };

        // action handlers
        void OnClose(wxCloseEvent& event);
        void OnButton(wxCommandEvent& event);
        void OnNewGame(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        // graphics and mechanics
        void clearBoard();
        void setUp();
        void tearDown();
        bool checkForWin();

        Settings *mSettings;
        Settings::box_t ***mBox;
        wxStaticLine **mLine;
        int mTurn;

        // opponent
        Opponent mOpponent;
        bool mUseOpponent;

        DECLARE_EVENT_TABLE();
};


#endif // TICTACTOEMAIN_H
