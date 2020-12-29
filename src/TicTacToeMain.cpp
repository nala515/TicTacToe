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
    setUp();
}


TicTacToeFrame::~TicTacToeFrame()
{
   for(unsigned int i = 0; i < mSettings->GetNumLines(); i++)
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
    clearBoard();
    tearDown();
    setUp();
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

// Clear the board of X's and O's
//
void TicTacToeFrame::clearBoard()
{
    // clear game board
    for(int i = 0; i < mSettings->GetNumRows(); i++)
    {
      for(int j = 0; j < mSettings->GetNumCols(); j++)
      {
         mBox[i][j]->button->SetLabel("");
         mTurn = 0;
      }
    }
}

// Draw the game area with lines and boxes
//
void TicTacToeFrame::setUp()
{
    int boxWidth = mSettings->GetBoxWidth();
    int marginSize = mSettings->GetMarginSize();
    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    // calculate box locations and insert text boxes
    mBox = new Settings::box_t**[numRows];
    for(int i = 0; i < numRows; i++)
    {
        mBox[i] = new Settings::box_t*[numCols];
        for(int j = 0; j < numCols; j++)
        {
            mBox[i][j] = new Settings::box_t;
            // top left pos
            mBox[i][j]->start = new wxPoint(marginSize + (boxWidth * i),
                                            marginSize + (boxWidth * j));
            // bottom right pos
            mBox[i][j]->stop = new wxPoint(mBox[i][j]->start->x + boxWidth,
                                           mBox[i][j]->start->y + boxWidth);

            // button
            mBox[i][j]->button = new wxButton (this, idButton, "", *mBox[i][j]->start,
                                               wxSize(boxWidth, boxWidth), wxBORDER_NONE,
 	                                           wxDefaultValidator, wxButtonNameStr);
            wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                        false, "", wxFONTENCODING_DEFAULT);
            mBox[i][j]->button->SetFont(font);
         }
    }
    // draw vertical lines
    mLine = new wxStaticLine*[numLines];
    for(int i = 0; i < numLines/2; i++)
    {
       mLine[i] = new wxStaticLine(this, wxID_ANY, *mBox[i][0]->stop, wxSize(1,boxWidth * numRows), wxLI_VERTICAL);
       mLine[i]->SetBackgroundColour(*wxBLACK);
    }
    // draw horizontal lines
    for(int i = numLines/2; i < numLines; i++)
    {
        mLine[i] = new wxStaticLine(this, wxID_ANY, *mBox[0][i-numLines/2]->stop, wxSize(boxWidth * numCols,1), wxLI_HORIZONTAL);
        mLine[i]->SetBackgroundColour(*wxBLACK);
    }
}

// Destroy the lines and boxes
//
void TicTacToeFrame::tearDown()
{
    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete mBox[i][j]->start;
            delete mBox[i][j]->stop;
            delete mBox[i][j]->button;
            delete mBox[i][j];
        }
        delete mBox[i];
    }
    delete mBox;
    for(int i = 0; i < numLines; i++)
    {
        delete mLine[i];
    }
    delete mLine;
}


// Check for a win.
// This is the only function that relies on the game area being 3x3.
//
bool TicTacToeFrame::checkForWin()
{
   // check rows for wins
   for(int i = 0; i < mSettings->GetNumRows(); i++)
   {
      if((mBox[i][0]->button->GetLabel() != "" ) &&
         (mBox[i][0]->button->GetLabel() == mBox[i][1]->button->GetLabel()) &&
         (mBox[i][1]->button->GetLabel() == mBox[i][2]->button->GetLabel()))
      {
         return true;
      }
   }
   // check cols for wins
   for(int j = 0; j < mSettings->GetNumCols(); j++)
   {
      if((mBox[0][j]->button->GetLabel() != "" ) &&
         (mBox[0][j]->button->GetLabel() == mBox[1][j]->button->GetLabel()) &&
         (mBox[1][j]->button->GetLabel() == mBox[2][j]->button->GetLabel()))
      {
         return true;
      }
   }
   // check left-right diagonal for win
   if((mBox[0][0]->button->GetLabel() != "" ) &&
      (mBox[0][0]->button->GetLabel() == mBox[1][1]->button->GetLabel()) &&
      (mBox[1][1]->button->GetLabel() == mBox[2][2]->button->GetLabel()))
   {
      return true;
   }
   // check right-left diagonal for win
   if((mBox[2][0]->button->GetLabel() != "" ) &&
      (mBox[2][0]->button->GetLabel() == mBox[1][1]->button->GetLabel()) &&
      (mBox[1][1]->button->GetLabel() == mBox[0][2]->button->GetLabel()))
   {
      return true;
   }
   return false;
}
