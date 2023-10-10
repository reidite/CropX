// Precompilation
#include "wx/wxprec.h"

#include "ScreenPanel.h"

// ----------------------------------------------------------------------------
// ScreenPanel
// ----------------------------------------------------------------------------

UI::ScreenFrame::ScreenFrame(int x, int y, int width, int height)
    : GUIScreenFrame(nullptr, wxID_ANY, wxString(""), wxPoint(x, y), wxSize(width, height))
{
    n_width = width;
    n_height = height;
}