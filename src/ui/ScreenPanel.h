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
		int n_width;
		int n_height;

		std::pair<unsigned int, unsigned int> pn_dpi;

		ScreenFrame(int x, int y, int width, int height);
		~ScreenFrame() {}


	};
}