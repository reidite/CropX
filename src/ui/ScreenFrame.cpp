// Precompilation
#include "wx/wxprec.h"

#include "ScreenFrame.h"

// ----------------------------------------------------------------------------
// ScreenPanel
// ----------------------------------------------------------------------------

UI::ScreenFrame::ScreenFrame(wxSize size)
    : GUIScreenFrame(nullptr, wxID_ANY, wxEmptyString) {
    wxRect displayRect(wxPoint(0, 0), size);
    SetSize(displayRect);
    Move(displayRect.GetPosition());

    this->Show(false);
}