/////////////////////////////////////////////////////////////////////////////
// Name:            main.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         09/10/2023
// Last edit:       17/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once

//---------------------------------------------------------------------------
// MainFrame
//---------------------------------------------------------------------------

//!< Definition of name and default size for the application main frame 
#define MAINFRAME_NAME "CropX"
#define MAINFRAME_WIDTH 200
#define MAINFRAME_HEIGHT 100

//!< Default delay value for the process active selecting object
#define DEFAULT_ACTIVE_DELAY 2000

#include <thread>

#include "GUI.h"
#include "SelectPanel.h"
#include "../func/capture.h"
#include "../func/provider.h"

namespace UI {
    /**  @class MainFrame
  
        Main frame of the application handling user inputs and events generated
        by the GUI elements contained within it.
        
        This class defines handling functions for getting inputs from the user
        to control the application.
    */
	class MainFrame : public GUIMainFrame {
	
    private:
        //!< Container of the selecting frame instance
        Custom::SelectPanel* m_frame_SelectFrame;

        Func::CaptureMechanism* m_captor;
        Func::Provider* m_provider;

        //!< Threads selecting coordinates to blit image from screen.
        std::thread* pthrd_SreenCropper;
        std::thread* pthrd_SreenActiveSelector;

        //!< Selecting panel setting position.
        void SettingSelectPanelFullScreen();
        void ResetingSelectPanelProperties();
        
        //!< Selecting thread initializers.
        void InitializingCroppingThread();
        void InitializingActiveThread();

    protected:
        //!< MainFrame Events
        void MainFrameUIOnClose(wxCloseEvent& event);

        //!< Screenshot Buttons Events
        void m_bpButton_FullOnButtonClick(wxCommandEvent& event);
        void m_bpButton_AreaOnButtonClick(wxCommandEvent& event);
        void m_bpButton_ActiveOnButtonClick(wxCommandEvent& event);

    public:
        MainFrame();
        ~MainFrame();
    };
}