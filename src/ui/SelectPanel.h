/////////////////////////////////////////////////////////////////////////////
// Name:            SelectPanel.cpp
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
#include <atomic>

#include <wx/dcbuffer.h>

#include "GUI.h"

namespace UI
{
	namespace Custom
	{
		class SelectPanel : public GUISelectFrame
		{
		private:

		protected:
			void GUISelectFrameOnClose(wxCloseEvent& event);
			void OnPaint(wxPaintEvent &event);

		public:
			std::atomic<bool>  atomic_b_croppingScreenIsRaised = false;

			SelectPanel();
		};
	}
}
