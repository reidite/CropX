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
    m_provider = new Func::Provider();

    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        wxDisplay display(i);
        wxRect screen = display.GetGeometry();
        mp_frame_ScreenFrames.push_back(nullptr);
        m_bitmap_Screens.push_back(nullptr);
        mp_frame_ScreenFrames[i] = new UI::ScreenFrame(screen.x, screen.y, screen.width, screen.height);
    }

    mp_frame_SelectFrame = new Custom::SelectPanel();

    
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
    ShowingScreenFrames();
    InitializingCroppingThread();
}

void UI::MainFrame::m_button_ActiveOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode = Func::Mode::Active;
    this->Show(false);
    m_captor->InitiatingRegionSelection();
    mp_frame_SelectFrame->SetPosition(wxPoint(30, 30));
    mp_frame_SelectFrame->SetSize(wxSize(50, 50));
    mp_frame_SelectFrame->Show(true);
    InitializingActiveThread();
    m_captor->mode = Func::Mode::None;
}

void UI::MainFrame::ShowingScreenFrames() {
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
    
    mp_frame_SelectFrame->SetPosition(wxPoint(30, 30));
    mp_frame_SelectFrame->SetSize(wxSize(50, 50));
    mp_frame_SelectFrame->Show(true);
}

void UI::MainFrame::HiddingScreenFrames() {
    mp_frame_SelectFrame->Show(false);
    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        mp_frame_ScreenFrames[i]->ShowFullScreen(false);
    }
}

void UI::MainFrame::InitializingCroppingThread() {
	pthrd_SreenCropper = new std::thread([&]() {
		while (!(mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised));
		GettingCaptureArea();
		mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
        for (int i = 0; i < wxDisplay::GetCount(); i++) {
            mp_frame_ScreenFrames[i]->ShowFullScreen(false);
            mp_frame_ScreenFrames[i]->gSizer_Screen->Clear(true);
        }
        mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
	});
}

void UI::MainFrame::InitializingActiveThread() {
    pthrd_SreenActiveSelector = new std::thread([&]() {
        while (!(mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised)) {
            wxPoint cursorPos = wxGetMousePosition();
            if (m_provider->GetActiveComponent(cursorPos.x, cursorPos.y)) {
                mp_frame_SelectFrame->SetPosition(wxPoint(m_provider->n_x, 
                                                            m_provider->n_y));
                mp_frame_SelectFrame->SetSize(wxSize(m_provider->width, 
                                                        m_provider->height));
            }
            Sleep(2000);
        }
        GettingCaptureArea();
        mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
    });
}

void UI::MainFrame::GettingCaptureArea() {
    int x, y, width, height;
    mp_frame_SelectFrame->GetPosition(&x, &y);
    mp_frame_SelectFrame->GetSize(&width, &height);
    m_captor->Cropping(x, y, width, height);

    mp_frame_SelectFrame->Show(false);
    this->Show(true);
    m_captor->mode = Func::Mode::None;
}

