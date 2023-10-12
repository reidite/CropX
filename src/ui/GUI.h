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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/statbmp.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxBitmapButton* m_bpButton_Full;
		wxBitmapButton* m_bpButton_Area;
		wxBitmapButton* m_bpButton_Active;
		
		// Virtual event handlers, overide them in your derived class
		virtual void MainFrameUIOnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void m_bpButton_FullOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_AreaOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_ActiveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 200,100 ), long style = wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP|wxSUNKEN_BORDER );
		
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUISelectFrame
///////////////////////////////////////////////////////////////////////////////
class GUISelectFrame : public wxFrame 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void GUISelectFrameOnClose( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISelectFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxFRAME_NO_TASKBAR|wxTRANSPARENT_WINDOW );
		
		~GUISelectFrame();
	
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
		wxStaticBitmap* m_bitmap_Screen;
		
		GUIScreenFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxFRAME_NO_TASKBAR|wxMAXIMIZE_BOX|wxNO_BORDER|wxTRANSPARENT_WINDOW );
		
		~GUIScreenFrame();
	
};

#endif //__GUI_H__
