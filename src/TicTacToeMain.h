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

#include <wx/button.h>
#include <wx/dcclient.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/wxprec.h>
#include <wx/wx.h>

struct box_t
{
   wxPoint begin;
   wxPoint end;
   wxButton *button;
};

namespace FrameSpace
{
   // constants
   static const int kNumRows = 3;
   static const int kNumCols = 3;
   static const int kNumBoxes = kNumRows * kNumCols;
   static const int kNumLines = kNumRows + kNumCols - 2;
   static const int kMarginSize = 100;
   static const int kBoxWidth = 100;
   static const int kWindowSize = (kMarginSize * 2) + (kNumCols * kBoxWidth);
};

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
        void OnClose(wxCloseEvent& event);
        void OnButton(wxCommandEvent& event);
        void OnNewGame(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void setUp();
        bool checkForWin();
        DECLARE_EVENT_TABLE();

        // graphics
        box_t mBox [FrameSpace::kNumRows][FrameSpace::kNumCols];
        wxStaticLine *mLine [FrameSpace::kNumLines];
        int mTurn;
};


#endif // TICTACTOEMAIN_H
