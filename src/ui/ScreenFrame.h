/////////////////////////////////////////////////////////////////////////////
// Name:            main.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         10/10/2023
// Last edit:       10/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "GUI.h"
#include "wx/display.h"

namespace UI {
	class ScreenFrame : public GUIScreenFrame
	{
	private:

	protected:

	public:

		ScreenFrame(wxSize size);
		~ScreenFrame() {}


	};
}