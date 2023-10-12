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
#if __WXGTK__
#define BORDERLESS_FRAME_STYLE (wxFRAME_NO_TASKBAR)
#else
#define BORDERLESS_FRAME_STYLE (wxFRAME_NO_TASKBAR | wxBORDER_NONE)
#endif
#define DEFAULT_RED_MARK_SIZE 15

#include <atomic>
#include "wx/wx.h"
#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include <wx/version.h>

#include "GUI.h"

namespace UI
{
	namespace Custom
	{
		class SelectPanel : public GUISelectFrame
		{
		private:
			enum RESIZE_MODE
			{
				None,
				FromTop,
				FromUpperLeft,
				FromLeft,
				FromLowerLeft,
				FromBottom,
				FromLowerRight,
				FromRight,
				FromUpperRight
			};
		protected:
			void GUISelectFrameOnClose(wxCloseEvent& event);


			// General event handlers
			void OnBgPanelPaint(wxPaintEvent&);

			// Event handlers for resizing
			void OnLeftDownForResizeFromUpperRight(wxMouseEvent&);
			void OnLeftDownForResizeFromUpperLeft(wxMouseEvent&);
			void OnLeftDownForResizeFromLowerRight(wxMouseEvent&);
			void OnLeftDownForResizeFromLowerLeft(wxMouseEvent&);

			void OnLeftUp(wxMouseEvent&);
			void OnMouseCaptureLost(wxMouseCaptureLostEvent&);
			void OnResizeTimer(wxTimerEvent&);

			// Resizing helper functions
			void DoDragBasedResize();
			void StartResize(wxWindow*, const wxPoint&);
			void CompleteResize(bool doFinalResize = false);

			// Data and objects needed for resizing.
			wxTimer m_resizeTimer;
			int m_resizeFrequency;
			int m_resizeAreaLength;
			RESIZE_MODE m_resizeMode;
			wxPoint m_resizeStartPoint;
			wxSize m_initialFrameSize;
			wxPoint m_initialFramePosition;

			wxWindow* m_clickToResizeFromUpperRightWindow;
			wxWindow* m_clickToResizeFromUpperLeftWindow;
			wxWindow* m_clickToResizeFromLowerRightWindow;
			wxWindow* m_clickToResizeFromLowerLeftWindow;
			wxWindow* m_curResizeWindow;

			// GUI controls
			wxPanel* m_bgPanel;
		public:
			std::atomic<bool>  atomic_b_croppingScreenIsRaised = false;

			SelectPanel();
		};
	}
}
