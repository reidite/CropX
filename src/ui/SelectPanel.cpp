#include "SelectPanel.h"

// --------------------------------------------------------------------------
// SelectPanel - Construction
// --------------------------------------------------------------------------

UI::Custom::SelectPanel::SelectPanel()
	: GUISelectFrame(nullptr, wxID_ANY, wxString(""), 
        wxDefaultPosition, wxDefaultSize, BORDERLESS_FRAME_STYLE) {
	// Set up the UI.
    SetTransparent(100);
	m_bgPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE);
	m_bgPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_bgPanel->Bind(wxEVT_PAINT, &SelectPanel::OnBgPanelPaint, this);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_bgPanel, wxSizerFlags(1).Expand());
    SetSizer(mainSizer);
    Layout();

    // Initialize the data needed for resizing.
    m_resizeMode = RESIZE_MODE::None;
    m_resizeAreaLength = FromDIP(RESIZE_AREA_SIZE);


    m_resizeTimer.Bind(wxEVT_TIMER, &SelectPanel::OnResizeTimer, this);
    m_resizeFrequency = 50;
    m_curResizeWindow = NULL;

    // Set event handlers for resizing.
    m_bgPanel->Bind(wxEVT_LEFT_DOWN,
        &SelectPanel::OnLeftDownForResizeFromUpperRight, this);
    m_bgPanel->Bind(wxEVT_LEFT_DOWN,
        &SelectPanel::OnLeftDownForResizeFromUpperLeft, this);
    m_bgPanel->Bind(wxEVT_LEFT_DOWN,
        &SelectPanel::OnLeftDownForResizeFromLowerRight, this);
    m_bgPanel->Bind(wxEVT_LEFT_DOWN,
        &SelectPanel::OnLeftDownForResizeFromLowerLeft, this);

    m_bgPanel->Bind(wxEVT_LEFT_UP,
        &SelectPanel::OnLeftUp, this);
    m_bgPanel->Bind(wxEVT_MOUSE_CAPTURE_LOST,
        &SelectPanel::OnMouseCaptureLost, this);

    // Set event handlers for initializing screen capture.
    m_bgPanel->Bind(wxEVT_LEFT_DOWN,
        &SelectPanel::OnLeftDownForInitCapturing, this);

    // Set event handlers for keyboard.
    m_bgPanel->Bind(wxEVT_KEY_DOWN,
        &SelectPanel::OnChar, this);
}

UI::Custom::SelectPanel::~SelectPanel() {}

// --------------------------------------------------------------------------
// SelectPanel - Event Handlers
// --------------------------------------------------------------------------

void UI::Custom::SelectPanel::OnLeftDownForInitCapturing(wxMouseEvent& event) {
    if (event.ControlDown()) {
        // Raising the tracking state to init the capturing thread.
        atomic_b_croppingScreenIsRaised = true;
        this->Show(false);
    }
    else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::OnChar(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_ESCAPE) {
        this->Close(true);
    }
    else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::GUISelectFrameOnClose(wxCloseEvent& event) {
    atomic_b_croppingScreenIsCanceled = true;
	atomic_b_croppingScreenIsRaised = true;
	this->Show(false);
}

void UI::Custom::SelectPanel::OnBgPanelPaint(wxPaintEvent&) {
    wxAutoBufferedPaintDC dc(m_bgPanel);

    dc.Clear();
    wxPen pen(wxColor(152, 0, 0), 5);
    dc.SetPen(pen);


    // Draw some red marks to indicate the upper left resize area
    wxPoint upperLeft = m_bgPanel->GetClientRect().GetTopLeft();
    dc.DrawLine(upperLeft + wxPoint(0, m_resizeAreaLength), upperLeft);
    dc.DrawLine(upperLeft, upperLeft + wxPoint(m_resizeAreaLength, 0));

    // Draw some red marks to indicate the upper right resize area
    wxPoint upperRight = m_bgPanel->GetClientRect().GetTopRight();
    dc.DrawLine(upperRight + wxPoint(0, m_resizeAreaLength), upperRight);
    dc.DrawLine(upperRight, upperRight - wxPoint(m_resizeAreaLength, 0));

    // Draw some red marks to indicate the lower left resize area
    wxPoint lowerLeft = m_bgPanel->GetClientRect().GetBottomLeft();
    dc.DrawLine(lowerLeft - wxPoint(0, m_resizeAreaLength), lowerLeft);
    dc.DrawLine(lowerLeft, lowerLeft + wxPoint(m_resizeAreaLength, 0));

    // Draw some red marks to indicate the lower right resize area
    wxPoint lowerRight = m_bgPanel->GetClientRect().GetBottomRight();
    dc.DrawLine(lowerRight - wxPoint(0, m_resizeAreaLength), lowerRight);
    dc.DrawLine(lowerRight, lowerRight - wxPoint(m_resizeAreaLength, 0));
}

void UI::Custom::SelectPanel::OnLeftDownForResizeFromUpperLeft(wxMouseEvent& event) {
    wxPoint p = event.GetPosition();
    wxSize sz = m_bgPanel->GetClientSize();

    // Check if the click is in the upper left of the window.
    if (p.x < m_resizeAreaLength &&
        p.y < m_resizeAreaLength) {
        StartResize(m_bgPanel, p);

        m_resizeMode = RESIZE_MODE::FromUpperLeft;

        SetCursor(wxCursor(wxCURSOR_SIZENESW));
    } else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::OnLeftDownForResizeFromUpperRight(wxMouseEvent& event) {
    wxPoint p = event.GetPosition();
    wxSize sz = m_bgPanel->GetClientSize();

    // Check if the click is in the upper right of the window.
    if (sz.GetWidth() - p.x < m_resizeAreaLength &&
        p.y < m_resizeAreaLength) {
        StartResize(m_bgPanel, p);

        m_resizeMode = RESIZE_MODE::FromUpperRight;

        SetCursor(wxCursor(wxCURSOR_SIZENWSE));
    } else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::OnLeftDownForResizeFromLowerLeft(wxMouseEvent& event) {
    wxPoint p = event.GetPosition();
    wxSize sz = m_bgPanel->GetClientSize();

    // Check if the click is in the lower left of the window.
    if (p.x < m_resizeAreaLength &&
        sz.GetHeight() - p.y < m_resizeAreaLength) {
        StartResize(m_bgPanel, p);

        m_resizeMode = RESIZE_MODE::FromLowerLeft;

        SetCursor(wxCursor(wxCURSOR_SIZENESW));
    } else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::OnLeftDownForResizeFromLowerRight(wxMouseEvent& event) {
    wxPoint p = event.GetPosition();
    wxSize sz = m_bgPanel->GetClientSize();

    // Check if the click is in the lower right of the window.
    if (sz.GetWidth() - p.x < m_resizeAreaLength &&
        sz.GetHeight() - p.y < m_resizeAreaLength) {
        StartResize(m_bgPanel, p);

        m_resizeMode = RESIZE_MODE::FromLowerRight;

        SetCursor(wxCursor(wxCURSOR_SIZENWSE));
    } else {
        event.Skip();
    }
}



void UI::Custom::SelectPanel::OnLeftUp(wxMouseEvent& event) {
    if (m_resizeMode != RESIZE_MODE::None) {
        CompleteResize(true);
    }
    else {
        event.Skip();
    }
}

void UI::Custom::SelectPanel::OnMouseCaptureLost(wxMouseCaptureLostEvent&) {
    if (m_resizeMode != RESIZE_MODE::None) {
        CompleteResize(false);
    }
}

void UI::Custom::SelectPanel::OnResizeTimer(wxTimerEvent&) {
    DoDragBasedResize();
}

// --------------------------------------------------------------------------
// SelectPanel - Functions
// --------------------------------------------------------------------------

void UI::Custom::SelectPanel::DoDragBasedResize() {
    wxMouseState ms = ::wxGetMouseState();
    wxPoint curMousePsn = ms.GetPosition();
    wxPoint dragVector = curMousePsn - m_resizeStartPoint;

    wxSize newSize(m_initialFrameSize);
    wxPoint newPsn(m_initialFramePosition);

    switch (m_resizeMode) {
    case RESIZE_MODE::FromUpperRight:
        newSize = wxSize(m_initialFrameSize.GetWidth() + dragVector.x,
            m_initialFrameSize.GetHeight() - dragVector.y);
        newPsn = wxPoint(m_initialFramePosition.x,
            m_initialFramePosition.y + dragVector.y);
        break;
    case RESIZE_MODE::FromUpperLeft:
        newSize = wxSize(m_initialFrameSize.GetWidth() - dragVector.x,
            m_initialFrameSize.GetHeight() - dragVector.y);
        newPsn = wxPoint(m_initialFramePosition.x + dragVector.x,
            m_initialFramePosition.y + dragVector.y);
        break;
    case RESIZE_MODE::FromLowerRight:
        newSize = wxSize(m_initialFrameSize.GetWidth() + dragVector.x,
            m_initialFrameSize.GetHeight() + dragVector.y);
        break;
    case RESIZE_MODE::FromLowerLeft:
        newSize = wxSize(m_initialFrameSize.GetWidth() - dragVector.x,
            m_initialFrameSize.GetHeight() + dragVector.y);

        newPsn = wxPoint(m_initialFramePosition.x + dragVector.x,
            m_initialFramePosition.y);
        break;
    }

    SetSize(newPsn.x, newPsn.y, newSize.GetWidth(), newSize.GetHeight());
}

void UI::Custom::SelectPanel::StartResize(wxWindow* win, const wxPoint& p) {
    m_curResizeWindow = win;
    m_resizeTimer.Start(m_resizeFrequency);
    m_resizeStartPoint = m_curResizeWindow->ClientToScreen(p);
    m_curResizeWindow->CaptureMouse();
    m_initialFramePosition = GetPosition();
    m_initialFrameSize = GetSize();
}

void UI::Custom::SelectPanel::CompleteResize(bool doFinalResize) {
    if (doFinalResize) {
        DoDragBasedResize();
    }

    m_resizeTimer.Stop();
    m_resizeMode = RESIZE_MODE::None;


    SetCursor(wxCursor(wxCURSOR_ARROW));

    if (m_curResizeWindow && m_curResizeWindow->HasCapture()) {
        m_curResizeWindow->ReleaseMouse();
    }

    m_curResizeWindow = NULL;
}

