#pragma once
/////////////////////////////////////////////////////////////////////////////
// Name:            capture.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         11/10/2023
// Last edit:       16/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
// Provider
//---------------------------------------------------------------------------

#include <thread>
#include <windows.h>
#include <ole2.h>
#include <minmax.h>
#include <uiautomation.h>
#include <uiautomationclient.h>

namespace Func{
    /** @class Provider

        Provider provides a functioning for the application accessing to the UI 
        elements properties on the client side.

        This class getting the correct rendering rectangle of each UI element
        which is pointed by the cursor.
    */
    class Provider {
    public:
        //!< Client UI rendering infos
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;

        Provider();
        ~Provider();
        //!< Container for the pointed client UI element
        IUIAutomationElement* element;
        //!< Container for the parent of the pointed client UI element
        IUIAutomationElement* parent;

        //!< Data retrieving functionality for the pointed UI element
        HRESULT GetActiveComponent(int cursor_x, int cursor_y);

    private:
        //!< Container for the UI element retrivor
        IUIAutomation* m_automation;
        //!< Container for the UI element traveller
        IUIAutomationTreeWalker* walker;
    };
}
