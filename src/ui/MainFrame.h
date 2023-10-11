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
#include <thread>

#include <wx/statbmp.h>

#include "GUI.h"
#include "ScreenPanel.h"
#include "SelectPanel.h"
#include "../func/capture.h"
#include "../func/provider.h"
#include "uiautomationcore.h"
//---------------------------------------------------------------------------
// MainFrame
//---------------------------------------------------------------------------

//!< Definition of name and default size for the application main frame 
#define MAINFRAME_NAME "CropX"
#define MAINFRAME_WIDTH 300
#define MAINFRAME_HEIGHT 100

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
        void m_button_FullOnButtonClick(wxCommandEvent& event);
        void m_button_AreaOnButtonClick(wxCommandEvent& event);
        void m_button_ActiveOnButtonClick(wxCommandEvent& event);
    private:
        std::vector<UI::ScreenFrame*> mp_frame_ScreenFrames;
        std::vector<wxStaticBitmap*> m_bitmap_Screens;

        Custom::SelectPanel* mp_frame_SelectFrame;

        std::thread* pthrd_SreenCropper;
        std::thread* pthrd_SreenActiveSelector;

        void ShowingScreenFrames();
        void HiddingScreenFrames();
        void InitializingCroppingThread();
        void InitializingActiveThread();
        void GettingCaptureArea();
    };
}