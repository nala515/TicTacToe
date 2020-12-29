#include "GameArea.h"

GameArea::GameArea()
{
    mSettings = Settings::getInstance();

    int numRows = mSettings->GetNumRows();
    // initialize rows
    mBoxes = new box_t*[numRows];
    for(int i = 0; i < mSettings->GetNumRows())
    {
        // initialize cols
        mBoxes[i] = new box_t;
    }
    setUp();
}

GameArea::~GameArea()
{
    //dtor
}


// Draw the game area with lines and boxes
//
void GameArea::setUp()
{
    int boxWidth = mSettings->GetBoxWidth();
    int marginSize = mSettings->GetMarginSize();
    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    // calculate box locations and insert text boxes
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            // top left pos
            mBox[i][j].start = wxPoint(marginSize + (boxWidth * i),
                                       marginSize + (boxWidth * j));
            // bottom right pos
            mBox[i][j].stop = wxPoint(mBox[i][j].start.x + boxWidth,
                                      mBox[i][j].start.y + boxWidth);

            // button
            mBox[i][j].button = wxButton (this, idButton, "", *mBox[i][j]->start,
                                           wxSize(boxWidth, boxWidth), wxBORDER_NONE,
 	                                       wxDefaultValidator, wxButtonNameStr);
            wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                        false, "", wxFONTENCODING_DEFAULT);
            mBox[i][j].button.SetFont(font);
         }
    }
    // draw vertical lines
    for(int i = 0; i < numLines/2; i++)
    {
       mLine[i] = wxStaticLine(this, wxID_ANY, mBox[i][0].stop, wxSize(1,boxWidth * numRows), wxLI_VERTICAL);
       mLine[i].SetBackgroundColour(*wxBLACK);
    }
    // draw horizontal lines
    for(int i = numLines/2; i < numLines; i++)
    {
        mLine[i] = new wxStaticLine(this, wxID_ANY, mBox[0][i-numLines/2].stop, wxSize(boxWidth * numCols,1), wxLI_HORIZONTAL);
        mLine[i].SetBackgroundColour(*wxBLACK);
    }
}


// Destroy the lines and boxes
//
void GameArea::tearDown()
{
    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete mBox[i][j].start;
            delete mBox[i][j].stop;
            delete mBox[i][j].button;
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


// Clear the board of X's and O's
//
void GameArea::clearBoard()
{
    // clear game board
    for(int i = 0; i < mSettings->GetNumRows(); i++)
    {
      for(int j = 0; j < mSettings->GetNumCols(); j++)
      {
         mBox[i][j].button.SetLabel("");
         mTurn = 0;
      }
    }
}

// Check for a win.
// This is the only function that relies on the game area being 3x3.
//
bool GameArea::checkForWin()
{
   // check rows for wins
   for(int i = 0; i < mSettings->GetNumRows(); i++)
   {
      if((mBox[i][0].button.GetLabel() != "" ) &&
         (mBox[i][0].button.GetLabel() == mBox[i][1].button.GetLabel()) &&
         (mBox[i][1].button.GetLabel() == mBox[i][2].button.GetLabel()))
      {
         return true;
      }
   }
   // check cols for wins
   for(int j = 0; j < mSettings->GetNumCols(); j++)
   {
      if((mBox[0][j].button.GetLabel() != "" ) &&
         (mBox[0][j].button.GetLabel() == mBox[1][j].button.GetLabel()) &&
         (mBox[1][j].button.GetLabel() == mBox[2][j].button.GetLabel()))
      {
         return true;
      }
   }
   // check left-right diagonal for win
   if((mBox[0][0].button.GetLabel() != "" ) &&
      (mBox[0][0].button.GetLabel() == mBox[1][1].button.GetLabel()) &&
      (mBox[1][1].button.GetLabel() == mBox[2][2].button.GetLabel()))
   {
      return true;
   }
   // check right-left diagonal for win
   if((mBox[2][0].button.GetLabel() != "" ) &&
      (mBox[2][0].button.GetLabel() == mBox[1][1].button.GetLabel()) &&
      (mBox[1][1].button.GetLabel() == mBox[0][2].button.GetLabel()))
   {
      return true;
   }
   return false;
}
