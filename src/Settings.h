#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/wx.h>

class Settings
{
    public:
       static Settings* getInstance();
       ~Settings();

        // basic structure for each square
        struct box_t
        {
           wxPoint begin;
           wxPoint end;
           wxButton *button;
        };

        // options set by the user from the settings dialog
        int GetNumRows() { return mNumRows; }
        void SetNumRows(int val) { mNumRows = val; }
        int GetNumCols() { return mNumCols; }
        void SetNumCols(int val) { mNumCols = val; }
        int GetMarginSize() { return mMarginSize; }
        void SetMarginSize(int val) { mMarginSize = val; }
        int GetBoxWidth() { return mBoxWidth; }
        void SetBoxWidth(int val) { mBoxWidth = val; }

        // options calculated based on the other values
        int GetNumBoxes() { return mNumRows * mNumCols; }
        int GetNumLines() { return mNumRows + mNumCols - 2; }
        int GetWindowSize() { return (mMarginSize * 2) + (mNumCols * mBoxWidth); }

    protected:

    private:
        Settings(); // private constructor
        static Settings* mInstance;

        int mNumRows;
        int mNumCols;
        int mMarginSize;
        int mBoxWidth;
};

#endif // SETTINGS_H
