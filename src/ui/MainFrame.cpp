// Precompilation
#include "wx/wxprec.h"

#include "MainFrame.h"

// ----------------------------------------------------------------------------
// MainFrame
// ----------------------------------------------------------------------------

UI::MainFrame::MainFrame()
    : GUIMainFrame(nullptr, wxID_ANY, MAINFRAME_NAME, wxDefaultPosition, wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT))
{
    m_captor = new Func::CaptureMechanism();

    // Set minimum size hints
    GetSizer()->SetSizeHints(this);
}

// ----------------------------------------------------------------------------
// MainFrame - Event Handlers
// ----------------------------------------------------------------------------

void UI::MainFrame::MainFrameUIOnClose(wxCloseEvent& event)
{
    Destroy();
}


void UI::MainFrame::m_button_FullOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode = Func::Mode::Full;
    m_captor->GrabbingImage();
    m_captor->mode = Func::Mode::None;
}

void UI::MainFrame::m_button_AreaOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode = Func::Mode::Area;
    m_captor->GrabbingImage();
    m_captor->mode = Func::Mode::None;
}

void UI::MainFrame::m_button_ActiveOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode = Func::Mode::Active;
    m_captor->GrabbingImage();
    m_captor->mode = Func::Mode::None;
}