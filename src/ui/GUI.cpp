///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_bpButton_Full = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	gSizer5->Add( m_bpButton_Full, 0, wxEXPAND, 5 );
	
	m_bpButton_Area = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	gSizer5->Add( m_bpButton_Area, 0, wxEXPAND, 5 );
	
	m_bpButton_Active = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	gSizer5->Add( m_bpButton_Active, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer5 );
	this->Layout();
	gSizer5->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMainFrame::MainFrameUIOnClose ) );
	m_bpButton_Full->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_FullOnButtonClick ), NULL, this );
	m_bpButton_Area->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_AreaOnButtonClick ), NULL, this );
	m_bpButton_Active->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_ActiveOnButtonClick ), NULL, this );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMainFrame::MainFrameUIOnClose ) );
	m_bpButton_Full->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_FullOnButtonClick ), NULL, this );
	m_bpButton_Area->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_AreaOnButtonClick ), NULL, this );
	m_bpButton_Active->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_bpButton_ActiveOnButtonClick ), NULL, this );
	
}

GUISelectFrame::GUISelectFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISelectFrame::GUISelectFrameOnClose ) );
}

GUISelectFrame::~GUISelectFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISelectFrame::GUISelectFrameOnClose ) );
	
}
