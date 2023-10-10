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
	this->SetSizeHints( wxSize( 200,100 ), wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_button_Full = new wxButton( this, wxID_ANY, wxT("Full"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_button_Full, 0, wxEXPAND, 10 );
	
	m_button_Area = new wxButton( this, wxID_ANY, wxT("Area"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_button_Area, 0, wxEXPAND, 10 );
	
	m_button_Active = new wxButton( this, wxID_ANY, wxT("Active"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_button_Active, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMainFrame::MainFrameUIOnClose ) );
	m_button_Full->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_FullOnButtonClick ), NULL, this );
	m_button_Area->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_AreaOnButtonClick ), NULL, this );
	m_button_Active->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_ActiveOnButtonClick ), NULL, this );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMainFrame::MainFrameUIOnClose ) );
	m_button_Full->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_FullOnButtonClick ), NULL, this );
	m_button_Area->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_AreaOnButtonClick ), NULL, this );
	m_button_Active->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::m_button_ActiveOnButtonClick ), NULL, this );
	
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

GUIScreenFrame::GUIScreenFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	gSizer_Screen = new wxGridSizer( 1, 1, 0, 0 );
	
	
	this->SetSizer( gSizer_Screen );
	this->Layout();
	
	this->Centre( wxBOTH );
}

GUIScreenFrame::~GUIScreenFrame()
{
}
