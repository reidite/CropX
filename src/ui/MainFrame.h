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
#pragma once
#include "GUI.h"
#include "../func/capture.h"
//---------------------------------------------------------------------------
// MainFrame
//---------------------------------------------------------------------------

//!< Definition of name and default size for the application main frame 
#define MAINFRAME_NAME "CropX"
#define MAINFRAME_WIDTH 780
#define MAINFRAME_HEIGHT 570

namespace UI {
    class MainFrame : public GUIMainFrame
    {
    public:
        MainFrame();
        ~MainFrame() {}

    protected:
        void MainFrameUIOnClose(wxCloseEvent& event);
        void m_button_FullOnButtonClick(wxCommandEvent& event);
        void m_button_AreaOnButtonClick(wxCommandEvent& event);
        void m_button_ActiveOnButtonClick(wxCommandEvent& event);
    private:
        Func::CaptureMechanism* m_captor;
    };
}