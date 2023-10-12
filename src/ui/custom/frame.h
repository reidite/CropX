/////////////////////////////////////////////////////////////////////////////
// Name:            main.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         11/10/2023
// Last edit:       11/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "windows.h"
#include "windowsx.h"
#include "stdio.h"
#include "stdlib.h"

#include "ole2.h"
#include "uiautomation.h"

namespace UI {
	namespace Custom {
		class Frame {
		public:
			Frame();
			virtual ~Frame();
			IRawElementProviderSimple* GetUIAutomationProvider(HWND hwnd);

		private:
			IRawElementProviderSimple* m_provider;
		};
	}
}