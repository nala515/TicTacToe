#include "GameArea.h"

GameArea::GameArea(wxFrame *frame, int buttonId)
    : mFrame(frame),
      mButtonId(buttonId),
      mGameActive(false)
{
    // initialize settings
    mSettings = Settings::getInstance();
}

GameArea::~GameArea()
{
    //dtor
}


// Draw the game area with lines and boxes
//
void GameArea::setUp()
{
    // if a game has been started, tear it down first
    if(mGameActive)
    {
        tearDown();
    }

    int boxWidth = mSettings->GetBoxWidth();
    int marginSize = mSettings->GetMarginSize();
    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    /* Draw boxes */

    // initialize rows
    for(int row = 0; row < numRows; row++)
    {
        // initialize cols
        std::vector<box_t*> colVec;
        for(int col = 0; col < numCols; col++)
        {
            box_t *box = new box_t;

            // calculate box locations and insert text boxes

            // top left pos
            box->start = wxPoint(marginSize + (boxWidth * row),
                                 marginSize + (boxWidth * col));
            // bottom right pos
            box->stop = wxPoint(box->start.x + boxWidth,
                                box->start.y + boxWidth);

            // button
            box->button = new wxButton (mFrame, mButtonId, "", box->start,
                                        wxSize(boxWidth, boxWidth), wxBORDER_NONE,
 	                                    wxDefaultValidator, wxButtonNameStr);
            wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                        false, "", wxFONTENCODING_DEFAULT);
            box->button->SetFont(font);

            colVec.push_back(box);
        }
        mBox.push_back(colVec);
    }

    /* Draw lines */

    // draw vertical lines
    for(int i = 0; i < numLines/2; i++)
    {
       wxStaticLine *line = new wxStaticLine(mFrame, wxID_ANY, mBox[i][0]->stop, wxSize(1,boxWidth * numRows), wxLI_VERTICAL);
       line->SetBackgroundColour(*wxBLACK);
       mLine.push_back(line);
    }
    // draw horizontal lines
    for(int i = numLines/2; i < numLines; i++)
    {
        wxStaticLine *line = new wxStaticLine(mFrame, wxID_ANY, mBox[0][i-numLines/2]->stop, wxSize(boxWidth * numCols,1), wxLI_HORIZONTAL);
        line->SetBackgroundColour(*wxBLACK);
        mLine.push_back(line);
    }

    /* Game on! */
    mGameActive = true;
}


// Destroy the lines and boxes
//
void GameArea::tearDown()
{
    // only tear down if a game had been previously set up
    if(!mGameActive) return;

    int numRows = mSettings->GetNumRows();
    int numCols = mSettings->GetNumCols();
    int numLines = mSettings->GetNumLines();

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete mBox[i][j]->button;
            delete mBox[i][j];
        }
    }
    mBox.clear();
    for(int i = 0; i < mLine.size(); i++)
    {
        delete mLine[i];
    }
    mLine.clear();

    // game off!
    mGameActive = false;
}


// Clear the board of X's and O's
//
void GameArea::clearBoard()
{
    // if game hasn't been set up, nothing to clear
    if(!mGameActive) return;

    // else clear game board
    for(int i = 0; i < mSettings->GetNumRows(); i++)
    {
      for(int j = 0; j < mSettings->GetNumCols(); j++)
      {
         mBox[i][j]->button->SetLabel("");
      }
    }
}

// Check for a win.
// This is the only function that relies on the game area being 3x3.
//
bool GameArea::checkForWin()
{
    // if game hasn't been set up, nothing to check
    if(!mGameActive) return false;

    // else check rows for wins
    for(int i = 0; i < mSettings->GetNumRows(); i++)
    {
        if((mBox[i][0]->button->GetLabel() != "" ) &&
           (mBox[i][0]->button->GetLabel() == mBox[i][1]->button->GetLabel()) &&
           (mBox[i][1]->button->GetLabel() == mBox[i][2]->button->GetLabel()))
        {
            // game over!!
            mGameActive = false;
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
            // game over!!
            mGameActive = false;
            return true;
        }
    }
    // check left-right diagonal for win
    if((mBox[0][0]->button->GetLabel() != "" ) &&
       (mBox[0][0]->button->GetLabel() == mBox[1][1]->button->GetLabel()) &&
       (mBox[1][1]->button->GetLabel() == mBox[2][2]->button->GetLabel()))
    {
        // game over!!
        mGameActive = false;
        return true;
    }
    // check right-left diagonal for win
    if((mBox[2][0]->button->GetLabel() != "" ) &&
       (mBox[2][0]->button->GetLabel() == mBox[1][1]->button->GetLabel()) &&
       (mBox[1][1]->button->GetLabel() == mBox[0][2]->button->GetLabel()))
    {
        // game over!!
        mGameActive = false;
        return true;
    }
    return false;
}
