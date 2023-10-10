///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxButton* m_button_Full;
		wxButton* m_button_Area;
		wxButton* m_button_Active;
		
		// Virtual event handlers, overide them in your derived class
		virtual void MainFrameUIOnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void m_button_FullOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_AreaOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_ActiveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,100 ), long style = wxDEFAULT_FRAME_STYLE|wxSUNKEN_BORDER );
		
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIScreenFrame
///////////////////////////////////////////////////////////////////////////////
class GUIScreenFrame : public wxFrame 
{
	private:
	
	protected:
	
	public:
		wxGridSizer* gSizer_Screen;
		
		GUIScreenFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 631,392 ), long style = wxFRAME_NO_TASKBAR|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxNO_BORDER );
		
		~GUIScreenFrame();
	
};

#endif //__GUI_H__
