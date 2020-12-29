#include "Settings.h"

Settings* Settings::mInstance = NULL;

// get instance
Settings* Settings::getInstance()
{
    if(!mInstance)
    {
        mInstance = new Settings();
    }
    return mInstance;
}

// constructor
Settings::Settings()
    : mNumRows(3),
      mNumCols(3),
      mMarginSize(100),
      mBoxWidth(100)
{
    //ctor
}

// destructor
Settings::~Settings()
{
    //dtor
}
