/////////////////////////////////////////////////////////////////////////////
// Name:            main.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         09/10/2023
// Last edit:       09/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#include "wx/app.h"
#include "wx/richtext/richtextxml.h"
#include "ui/Mainframe.h"

//---------------------------------------------------------------------------
// CropX
//---------------------------------------------------------------------------

class CropX : public wxApp {
/** Main class of the application, initializing the program, 
*   setting up any necessary resources.
*/
private:
    //!< Container of the main frame instance
    UI::MainFrame* mp_frame_MainFrame;

    

public:
    CropX() { }

    //!< Called before OnRun() to do initialization
    bool OnInit() wxOVERRIDE;

	wxDECLARE_NO_COPY_CLASS(CropX);
};


bool CropX::OnInit() {
    /**
    * Setting up resources on initializing time of the application.
    *
    */
    if (!wxApp::OnInit())
        return false;
    // Init all Image handlers
    wxInitAllImageHandlers();

    // Add richtext extra handlers (plain text is automatically added)
    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);

    mp_frame_MainFrame = new UI::MainFrame();

    mp_frame_MainFrame->SetIcon(wxIcon("IDB_PNG_FULL", 32, 32));
    mp_frame_MainFrame->Show(true);

    return true;
}


wxIMPLEMENT_APP(CropX);

