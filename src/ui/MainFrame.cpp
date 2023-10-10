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

    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        wxDisplay display(i);
        wxRect screen = display.GetGeometry();
        mp_frame_ScreenFrames.push_back(nullptr);
        m_bitmap_Screens.push_back(nullptr);
        mp_frame_ScreenFrames[i] = new UI::ScreenFrame(screen.x, screen.y, screen.width, screen.height);
    }

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
    this->Show(false);
    m_captor->InitiatingRegionSelection();
    int posX = 0, posY = 0;
    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        wxSize disSize = wxSize(mp_frame_ScreenFrames[i]->n_width,
                                mp_frame_ScreenFrames[i]->n_height);
        const wxBitmap tmp_Bitmap = m_captor->m_bitmap_Buffer->GetSubBitmap(wxRect(wxPoint(posX, posY), disSize));
        m_bitmap_Screens[i] = new wxStaticBitmap(mp_frame_ScreenFrames[i],
            wxID_ANY,
            wxBitmapBundle::FromBitmap(tmp_Bitmap),
            wxDefaultPosition,
            disSize);
        mp_frame_ScreenFrames[i]->gSizer_Screen->Add(m_bitmap_Screens[i], 0, wxEXPAND, 5);
        posX += disSize.x;
        mp_frame_ScreenFrames[i]->ShowFullScreen(true);
    }
    m_captor->mode = Func::Mode::None;
}

void UI::MainFrame::m_button_ActiveOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode = Func::Mode::Active;
    m_captor->GrabbingImage();
    m_captor->mode = Func::Mode::None;
}

void UI::MainFrame::ShowingScreenFrames() {
    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        mp_frame_ScreenFrames[i]->ShowFullScreen(true);
    }
}

void UI::MainFrame::HiddingScreenFrames() {
    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        mp_frame_ScreenFrames[i]->ShowFullScreen(false);
    }
}