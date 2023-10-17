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
#include <thread>

#include <wx/statbmp.h>

#include "GUI.h"
#include "ScreenFrame.h"
#include "SelectPanel.h"
#include "../func/capture.h"
#include "../func/provider.h"


#ifdef _WIN32
//windows code goes here
#include "windows.h"
#include "uiautomationcore.h"
#include "shellscalingapi.h"

#elif __linux__
//linux  code goes here

#elif __WXMAC__
//mac code goes here

#else

#endif


//---------------------------------------------------------------------------
// MainFrame
//---------------------------------------------------------------------------

//!< Definition of name and default size for the application main frame 
#define MAINFRAME_NAME "CropX"
#define MAINFRAME_WIDTH 225
#define MAINFRAME_HEIGHT 100

#define DEFAULT_ACTIVE_DELAY 2000
namespace UI {
    class MainFrame : public GUIMainFrame
    {
    public:
        Func::CaptureMechanism* m_captor;
        Func::Provider* m_provider;

        MainFrame();
        ~MainFrame() {}

    protected:
        void MainFrameUIOnClose(wxCloseEvent& event);
        void m_bpButton_FullOnButtonClick(wxCommandEvent& event);
        void m_bpButton_AreaOnButtonClick(wxCommandEvent& event);
        void m_bpButton_ActiveOnButtonClick(wxCommandEvent& event);
    private:
        Custom::SelectPanel* m_frame_SelectFrame;

        std::thread* pthrd_SreenCropper;
        std::thread* pthrd_SreenActiveSelector;

        void ShowingScreenFrame();
        void SettingSelectPanelFullScreen();
        void ResetingSelectPanelProperties();
        void InitializingCroppingThread();
        void InitializingActiveThread();
        void GettingCaptureArea();
    };
}