/***************************************************************
 * Name:      TicTacToeMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Jacqueline Robinson ()
 * Created:   2020-12-19
 * Copyright: Jacqueline Robinson ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TicTacToeMain.h"

#include <iostream>
#include <wx/colour.h>
#include <wx/dialog.h>
#include <wx/font.h>

using namespace std;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(TicTacToeFrame, wxFrame)
    EVT_CLOSE(TicTacToeFrame::OnClose)
    EVT_MENU(idNewGame,    TicTacToeFrame::OnNewGame)
    EVT_MENU(idMenuQuit,   TicTacToeFrame::OnQuit)
    EVT_MENU(idMenuAbout,  TicTacToeFrame::OnAbout)
    EVT_BUTTON(idButton,  TicTacToeFrame::OnButton)
END_EVENT_TABLE()


// Constructor
TicTacToeFrame::TicTacToeFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size),
      mTurn(0),
      mOpponent(),
      mUseOpponent(false)
{
    // file menu
    wxMenu *menuFile = new wxMenu;
    wxMenu *menuHelp = new wxMenu;
    wxMenuBar *menuBar = new wxMenuBar;
    menuFile->Append(idNewGame, "&New Gameeee",
                    "Start a new game");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // help menu
    menuHelp->Append(wxID_ABOUT);

    // menu bar
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();

    // game settings
    mSettings = Settings::getInstance();
    //setUp();
}


TicTacToeFrame::~TicTacToeFrame()
{
}

// Handle when the user exits.
//
void TicTacToeFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

// Handle when the user exits.
//
void TicTacToeFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

// Handle when the user clicks About.
//
void TicTacToeFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("About Tic-Tac-Toe"),
                 wxOK | wxICON_INFORMATION );
}

// Handle when a user selects a square to play.
//
void TicTacToeFrame::OnButton(wxCommandEvent& event)
{
   wxButton *button = dynamic_cast<wxButton*>(event.GetEventObject());
   if(button->GetLabel() != "")
   {
      return;
   }
   if(mTurn % 2 == 0)
   {
      button->SetLabel("X");
   }
   else
   {
      button->SetLabel("O");
   }

   // Next turn
   mTurn++;

   // Check if game is over
   if(true)//checkForWin())
   {
      // end the game if someone wins
      wxLogMessage("You win!");
   }
   else if(mTurn == mSettings->GetNumBoxes())
   {
      // end the game if no more boxes available
      wxLogMessage("Draw");
   }
}

// Handle when the user wants to start a new game.
//
void TicTacToeFrame::OnNewGame(wxCommandEvent& event)
{
    // todo: destroy existing game board first
    //clearBoard();
    //tearDown();
    //setUp();
    //wxMessageDialog *dlg = new wxMessageDialog(this, "New Game Settings", "Caption", wxOK, wxDefaultPosition);
    //wxMessageDialog *dlg = new wxMessageDialog(this, wxID_ANY, "New Game Settings", wxDefaultPosition, wxDefaultSize,
    //                                           wxOK | wxSTAY_ON_TOP | wxDEFAULT_DIALOG_STYLE, "New Game Settings");
    //if ( dlg->ShowModal() == wxID_OK )
    //{
    //    setUp();
   // }
    //else: dialog was cancelled or some another button pressed
    //dlg->Destroy();
}

