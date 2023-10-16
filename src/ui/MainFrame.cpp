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
        ;
        wxRect screen = display.GetGeometry();
        mp_frame_ScreenFrames.push_back(nullptr);
        mp_frame_ScreenFrames[i] = new UI::ScreenFrame(screen.x, screen.y, screen.width, screen.height);
        mp_frame_ScreenFrames[i]->Show(false);
    }

    GettingDPIScreenFrames();

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
    exit(0);
}


void UI::MainFrame::m_bpButton_FullOnButtonClick(wxCommandEvent& event)
{
    m_captor->m_capturingMode = Func::Mode::Full;
    m_captor->Capture();
    m_captor->m_capturingMode = Func::Mode::None;
}

void UI::MainFrame::m_bpButton_AreaOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->m_capturingMode = Func::Mode::Area;
    m_captor->Capture();
    ShowingScreenFrames();
    ResetingSelectFrameProperties();
    InitializingCroppingThread();
}

void UI::MainFrame::m_bpButton_ActiveOnButtonClick(wxCommandEvent& event)
{
    this->Show(false);
    m_captor->m_capturingMode = Func::Mode::Active;
    
    m_captor->Capture();
    ResetingSelectFrameProperties();
    InitializingActiveThread();
}

void UI::MainFrame::GettingDPIScreenFrames() {
    std::vector<std::pair<int, int>> dpiValues;

    std::vector<HMONITOR> monitors;
    auto monitorEnumProc = [](HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) -> BOOL
    {
        // Add the monitor handle to the vector
        std::vector<HMONITOR>* monitorHandles = reinterpret_cast<std::vector<HMONITOR>*>(dwData);
        monitorHandles->push_back(hMonitor);

        return TRUE;
    };
    EnumDisplayMonitors(NULL, NULL, monitorEnumProc, reinterpret_cast<LPARAM>(&monitors));

    for (int i = 0; i < monitors.size(); i++) {
        UINT dpiX = 0;
        UINT dpiY = 0;
        GetDpiForMonitor(monitors[i], MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
        mp_frame_ScreenFrames[i]->pn_effectiveDPI.first = dpiX;
        mp_frame_ScreenFrames[i]->pn_effectiveDPI.second = dpiY;
        GetDpiForMonitor(monitors[i], MDT_ANGULAR_DPI, &dpiX, &dpiY);
        mp_frame_ScreenFrames[i]->pn_angularDPI.first = dpiX;
        mp_frame_ScreenFrames[i]->pn_angularDPI.second = dpiY;
        GetDpiForMonitor(monitors[i], MDT_RAW_DPI, &dpiX, &dpiY);
        mp_frame_ScreenFrames[i]->pn_rawDPI.first = dpiX;
        mp_frame_ScreenFrames[i]->pn_rawDPI.second = dpiY;
    }
}

void UI::MainFrame::ShowingScreenFrames() {
    int posX = 0, posY = 0;
    for (int i = 0; i < wxDisplay::GetCount(); i++) {
        wxSize disSize = wxSize(mp_frame_ScreenFrames[i]->n_width,
            mp_frame_ScreenFrames[i]->n_height);
        const wxBitmap tmp_Bitmap = m_captor->m_bitmap_Buffer.GetSubBitmap(wxRect(wxPoint(posX, posY), disSize));
        mp_frame_ScreenFrames[i]->m_bitmap_Screen->SetBitmap(wxBitmapBundle::FromBitmap(tmp_Bitmap));

        posX += disSize.x;
        mp_frame_ScreenFrames[i]->Show(true);
    }
}

void UI::MainFrame::ResetingSelectFrameProperties() {
    mp_frame_SelectFrame->SetPosition(wxPoint(30, 30));
    mp_frame_SelectFrame->SetSize(wxSize(150, 150));
    mp_frame_SelectFrame->Show(true);
}

void UI::MainFrame::InitializingCroppingThread() {
	pthrd_SreenCropper = new std::thread([&]() {
		while (!(mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised));
		GettingCaptureArea();
		mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
        for (int i = 0; i < wxDisplay::GetCount(); i++) {
            mp_frame_ScreenFrames[i]->Show(false);
        }
        mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
	});
}

void UI::MainFrame::InitializingActiveThread() {
    pthrd_SreenActiveSelector = new std::thread([&]() {
        while (!(mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised)) {
            wxPoint cursorPos = wxGetMousePosition();
            mp_frame_SelectFrame->Show(false);
            if (SUCCEEDED(m_provider->GetActiveComponent(cursorPos.x, cursorPos.y))) {
                mp_frame_SelectFrame->SetPosition(wxPoint(m_provider->n_x, 
                                                            m_provider->n_y));
                mp_frame_SelectFrame->SetSize(wxSize(m_provider->width, 
                                                        m_provider->height));
            }
            mp_frame_SelectFrame->Show(true);
            Sleep(DEFAULT_ACTIVE_DELAY);
        }
        GettingCaptureArea();
        mp_frame_SelectFrame->atomic_b_croppingScreenIsRaised = false;
    });
}

void UI::MainFrame::GettingCaptureArea() {
    int x, y, width, height;
    mp_frame_SelectFrame->GetPosition(&x, &y);
    mp_frame_SelectFrame->GetSize(&width, &height);
    m_captor->Crop(x, y, width, height);

    this->Raise();
    this->Show(true);
    m_captor->m_capturingMode = Func::Mode::None;
}

