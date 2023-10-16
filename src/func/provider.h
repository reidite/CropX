#pragma once
/////////////////////////////////////////////////////////////////////////////
// Name:            capture.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         11/10/2023
// Last edit:       11/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <windows.h>
#include <ole2.h>
#include <minmax.h>
#include <uiautomation.h>
#include <uiautomationclient.h>

namespace Func{
    class Provider
    {
    public:
        unsigned int n_x;
        unsigned int n_y;
        unsigned int width;
        unsigned int height;

        Provider();
        IUIAutomationElement* element;
        IUIAutomationElement* parent;
        HRESULT GetActiveComponent(int x, int y);

    private:
        ~Provider();
        
        IUIAutomation* m_automation;
        IUIAutomationTreeWalker* walker;
    };
}
