// Precompilation
#include "wx/wxprec.h"

#include "MainFrame.h"

// --------------------------------------------------------------------------
// MainFrame - Construction
// --------------------------------------------------------------------------

UI::MainFrame::MainFrame()
    : GUIMainFrame(nullptr, wxID_ANY, MAINFRAME_NAME, wxDefaultPosition,
        wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT)) {
    m_bpButton_Full->SetBitmap(wxBitmapBundle(
        wxBitmap(wxT("src/res/full.big.png"), wxBITMAP_TYPE_ANY)));
    m_bpButton_Area->SetBitmap(wxBitmapBundle(
        wxBitmap(wxT("src/res/area.big.png"), wxBITMAP_TYPE_ANY)));
    m_bpButton_Active->SetBitmap(wxBitmapBundle(
        wxBitmap(wxT("src/res/active.big.png"), wxBITMAP_TYPE_ANY)));
    m_captor = new Func::CaptureMechanism();
    m_provider = new Func::Provider();
    m_frame_SelectFrame = new Custom::SelectPanel();
}

UI::MainFrame::~MainFrame() {
    delete m_captor;
    delete m_provider;
    if (pthrd_SreenCropper) {
        pthrd_SreenCropper->join();
        delete pthrd_SreenCropper;
    }
    if (pthrd_SreenActiveSelector) {
        pthrd_SreenActiveSelector->join();
        delete pthrd_SreenActiveSelector;
    }
    m_frame_SelectFrame->Destroy();
}

// --------------------------------------------------------------------------
// MainFrame - Event Handlers
// --------------------------------------------------------------------------

void UI::MainFrame::MainFrameUIOnClose(wxCloseEvent& event) {
    Destroy();
}

void UI::MainFrame::m_bpButton_FullOnButtonClick(wxCommandEvent& event) {
    m_captor->mode_captureType = Func::Mode::Full;
    SettingSelectPanelFullScreen();
    m_captor->Capture(m_frame_SelectFrame);
}

void UI::MainFrame::m_bpButton_AreaOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->mode_captureType = Func::Mode::Area;
    ResetingSelectPanelProperties();
    InitializingCroppingThread();
}

void UI::MainFrame::m_bpButton_ActiveOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->mode_captureType = Func::Mode::Active;
    ResetingSelectPanelProperties();
    InitializingActiveThread();
}

// --------------------------------------------------------------------------
// MainFrame - Functions
// --------------------------------------------------------------------------

void UI::MainFrame::SettingSelectPanelFullScreen() {
    m_frame_SelectFrame->SetPosition(m_captor->pts_mostUpperLeftPosition);
    m_frame_SelectFrame->SetSize(m_captor->size_fullExtendedPhysicalDisplay);
}

void UI::MainFrame::ResetingSelectPanelProperties() {
    m_frame_SelectFrame->SetPosition(wxPoint(100, 100));
    m_frame_SelectFrame->SetSize(wxSize(300,100));
    m_frame_SelectFrame->Show(true);
}

void UI::MainFrame::InitializingCroppingThread() {
    if (pthrd_SreenCropper) {
        pthrd_SreenCropper->join();
        delete pthrd_SreenCropper;
    }
	pthrd_SreenCropper = new std::thread([&]() {
		while (!(m_frame_SelectFrame->atomic_b_croppingScreenIsRaised));
        m_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
        if (m_frame_SelectFrame->atomic_b_croppingScreenIsCanceled)
            m_frame_SelectFrame->atomic_b_croppingScreenIsCanceled = false;
        else
            m_captor->Capture(m_frame_SelectFrame);
        this->Raise();
        this->Show(true);
	});
}

void UI::MainFrame::InitializingActiveThread() {
    if (pthrd_SreenActiveSelector) {
        pthrd_SreenActiveSelector->join();
        delete pthrd_SreenActiveSelector;
    }
    pthrd_SreenActiveSelector = new std::thread([&]() {
        while (!(m_frame_SelectFrame->atomic_b_croppingScreenIsRaised)) {
            wxPoint cursorPos = wxGetMousePosition();
            m_frame_SelectFrame->Show(false);
            if (SUCCEEDED(m_provider->GetActiveComponent(cursorPos.x, cursorPos.y))) {
                m_frame_SelectFrame->SetPosition(wxPoint(m_provider->x,
                                                            m_provider->y));
                m_frame_SelectFrame->SetSize(wxSize(m_provider->width,
                                                        m_provider->height));
                m_frame_SelectFrame->Raise();
            }
            m_frame_SelectFrame->Show(true);
            Sleep(DEFAULT_ACTIVE_DELAY);
        }
        m_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
        if (m_frame_SelectFrame->atomic_b_croppingScreenIsCanceled)
            m_frame_SelectFrame->atomic_b_croppingScreenIsCanceled = false;
        else
            m_captor->Capture(m_frame_SelectFrame);
        this->Raise();
        this->Show(true);
    });
}