#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

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

#endif // GLOBALS_H_INCLUDED
