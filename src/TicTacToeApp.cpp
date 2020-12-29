/***************************************************************
 * Name:      TicTacToeApp.cpp
 * Purpose:   Code for Application Class
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

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "TicTacToeApp.h"
#include "TicTacToeMain.h"

#include <wx/statline.h>
#include <wx/colour.h>

IMPLEMENT_APP(TicTacToeApp);

bool TicTacToeApp::OnInit()
{
    TicTacToeFrame *frame = new TicTacToeFrame("Tic-Tac-Toe", wxPoint(50, 50), wxSize(500, 550));
    frame->Show( true );

    return true;
}
