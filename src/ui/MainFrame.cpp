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

    m_frame_ScreenFrame = new UI::ScreenFrame(m_captor->size_fullExtendedLogicalDisplay);

    m_frame_SelectFrame = new Custom::SelectPanel();

    // Set minimum size hints
    GetSizer()->SetSizeHints(this);
}

// ----------------------------------------------------------------------------
// MainFrame - Event Handlers
// ----------------------------------------------------------------------------

void UI::MainFrame::MainFrameUIOnClose(wxCloseEvent& event)
{
    Destroy();
    exit(0);
}


void UI::MainFrame::m_bpButton_FullOnButtonClick(wxCommandEvent& event)
{
    m_captor->mode_captureType = Func::Mode::Full;
    SettingSelectPanelFullScreen();
    m_captor->Capture(m_frame_SelectFrame);
}

void UI::MainFrame::m_bpButton_AreaOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->mode_captureType = Func::Mode::Area;
    m_captor->Capture(m_frame_SelectFrame);
    ShowingScreenFrame();
    ResetingSelectPanelProperties();
    InitializingCroppingThread();
}

void UI::MainFrame::m_bpButton_ActiveOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->mode_captureType = Func::Mode::Active;
    
    m_captor->Capture(m_frame_SelectFrame);
    ResetingSelectPanelProperties();
    InitializingActiveThread();
}

void UI::MainFrame::ShowingScreenFrame() {
    m_frame_ScreenFrame->m_bitmap_Screen->SetBitmap(
        wxBitmapBundle::FromBitmap(m_captor->bitmap_Display));
    m_frame_ScreenFrame->Show(true);
}

void UI::MainFrame::SettingSelectPanelFullScreen() {
    m_frame_SelectFrame->SetPosition(wxPoint(0, 0));
    m_frame_SelectFrame->SetSize(m_captor->size_fullExtendedPhysicalDisplay);
}

void UI::MainFrame::ResetingSelectPanelProperties() {
    m_frame_SelectFrame->SetPosition(wxDefaultPosition);
    m_frame_SelectFrame->SetSize(wxDefaultSize);
    m_frame_SelectFrame->Show(true);
}

void UI::MainFrame::InitializingCroppingThread() {
	pthrd_SreenCropper = new std::thread([&]() {
		while (!(m_frame_SelectFrame->atomic_b_croppingScreenIsRaised));
        m_captor->Crop(m_frame_SelectFrame->GetScreenRect());
        this->Raise();
        this->Show(true);
		m_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
        m_frame_ScreenFrame->Show(false);
	});
}

void UI::MainFrame::InitializingActiveThread() {
    pthrd_SreenActiveSelector = new std::thread([&]() {
        while (!(m_frame_SelectFrame->atomic_b_croppingScreenIsRaised)) {
            wxPoint cursorPos = wxGetMousePosition();
            m_frame_SelectFrame->Show(false);
            if (SUCCEEDED(m_provider->GetActiveComponent(cursorPos.x, cursorPos.y))) {
                m_frame_SelectFrame->SetPosition(wxPoint(m_provider->n_x,
                                                            m_provider->n_y));
                m_frame_SelectFrame->SetSize(wxSize(m_provider->width,
                                                        m_provider->height));
            }
            m_frame_SelectFrame->Show(true);
            Sleep(DEFAULT_ACTIVE_DELAY);
        }
        m_captor->Crop(m_frame_SelectFrame->GetScreenRect());
        
        this->Raise();
        this->Show(true);
        m_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
    });
}