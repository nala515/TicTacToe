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
#include <wx/font.h>

using namespace std;
using namespace FrameSpace;

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
      mTurn(0)
{
/*
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR
*/
   wxMenu *menuFile = new wxMenu;
   menuFile->Append(idNewGame, "&New Game\tCtrl-H",
                    "Start a new game");
   menuFile->AppendSeparator();
   menuFile->Append(wxID_EXIT);
   wxMenu *menuHelp = new wxMenu;
   menuHelp->Append(wxID_ABOUT);
   wxMenuBar *menuBar = new wxMenuBar;
   menuBar->Append( menuFile, "&File" );
   menuBar->Append( menuHelp, "&Help" );
   SetMenuBar( menuBar );
   CreateStatusBar();

   // Pop-up
//test
   setUp();

}


TicTacToeFrame::~TicTacToeFrame()
{
   for(unsigned int i = 0; i < kNumLines; i++)
   {
      delete mLine[i];
   }
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
   if(checkForWin())
   {
      // end the game
      wxLogMessage("You win!");
   }
   else if(mTurn == kNumBoxes)
   {
      // end the game
      wxLogMessage("Draw");
   }
}

// Handle when the user wants to start a new game.
//
void TicTacToeFrame::OnNewGame(wxCommandEvent& event)
{
    // clear game board
    for(int i = 0; i < kNumRows; i++)
    {
      for(int j = 0; j < kNumCols; j++)
      {
         mBox[i][j].button->SetLabel("");
         mTurn = 0;
      }
    }
}

// Set up the game area upon application startup.
//
void TicTacToeFrame::setUp()
{
   // calculate box locations and insert text boxes
   for(int i = 0; i < kNumRows; i++)
   {
      for(int j = 0; j < kNumCols; j++)
      {
         // top left pos
         mBox[i][j].begin = wxPoint(kMarginSize + (kBoxWidth * i),
                                    kMarginSize + (kBoxWidth * j));
         // bottom right pos
         mBox[i][j].end = wxPoint(mBox[i][j].begin.x + kBoxWidth,
                                  mBox[i][j].begin.y + kBoxWidth);

         // button
         mBox[i][j].button = new wxButton (this, idButton, "", mBox[i][j].begin,
                             wxSize(kBoxWidth, kBoxWidth), wxBORDER_NONE,
 	                         wxDefaultValidator, wxButtonNameStr);
         wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                     false, "", wxFONTENCODING_DEFAULT);
         mBox[i][j].button->SetFont(font);
      }
   }
   // draw vertical lines
   for(int i = 1; i < kNumRows; i++)
   {
      mLine[i] = new wxStaticLine(this, wxID_ANY,
                 mBox[i][0].begin, wxSize(1,300), wxLI_VERTICAL);
      mLine[i]->SetBackgroundColour(*wxBLACK);
   }
   // draw horizontal lines
   for(int i = 1; i < kNumCols; i++)
   {
      mLine[i] = new wxStaticLine(this, wxID_ANY,
                     mBox[0][i].begin, wxSize(300,1), wxLI_HORIZONTAL);
      mLine[i]->SetBackgroundColour(*wxBLACK);
   }
}


// Check for a win.
// This is the only function that relies on the game area being 3x3.
//
bool TicTacToeFrame::checkForWin()
{
   // check rows for wins
   for(int i = 0; i < kNumRows; i++)
   {
      if((mBox[i][0].button->GetLabel() != "" ) &&
         (mBox[i][0].button->GetLabel() == mBox[i][1].button->GetLabel()) &&
         (mBox[i][1].button->GetLabel() == mBox[i][2].button->GetLabel()))
      {
         return true;
      }
   }
   // check cols for wins
   for(int j = 0; j < kNumCols; j++)
   {
      if((mBox[0][j].button->GetLabel() != "" ) &&
         (mBox[0][j].button->GetLabel() == mBox[1][j].button->GetLabel()) &&
         (mBox[1][j].button->GetLabel() == mBox[2][j].button->GetLabel()))
      {
         return true;
      }
   }
   // check left-right diagonal for win
   if((mBox[0][0].button->GetLabel() != "" ) &&
      (mBox[0][0].button->GetLabel() == mBox[1][1].button->GetLabel()) &&
      (mBox[1][1].button->GetLabel() == mBox[2][2].button->GetLabel()))
   {
      return true;
   }
   // check right-left diagonal for win
   if((mBox[2][0].button->GetLabel() != "" ) &&
      (mBox[2][0].button->GetLabel() == mBox[1][1].button->GetLabel()) &&
      (mBox[1][1].button->GetLabel() == mBox[0][2].button->GetLabel()))
   {
      return true;
   }
   return false;
}
