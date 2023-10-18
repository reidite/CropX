/////////////////////////////////////////////////////////////////////////////
// Name:            SelectPanel.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         10/10/2023
// Last edit:       17/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once

//---------------------------------------------------------------------------
// SelectPanel
//---------------------------------------------------------------------------

#if __WXGTK__
#define BORDERLESS_FRAME_STYLE (wxFRAME_NO_TASKBAR)
#else
#define BORDERLESS_FRAME_STYLE (wxFRAME_NO_TASKBAR | wxBORDER_NONE)
#endif
#define RESIZE_AREA_SIZE 15

#include <atomic>
#include "wx/wx.h"
#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include <wx/version.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "GUI.h"

namespace UI {
	namespace Custom {
		/**  @class SelectPanel
		
		Select panel of the application getting screen coordinate from the
		user and handling user adjustments.

		This class defines handling functions for getting inputs from the user
		to get the screen coordinate.
		*/
		class SelectPanel : public GUISelectFrame {

		private:
			/** Command IDs used for resizing the selecting window */
			enum RESIZE_MODE {
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
			//!< Event handler for initializing screen capture
			void OnLeftDownForInitCapturing(wxMouseEvent& event);

			//!< Event handler for keyboard
			void OnChar(wxKeyEvent& event);

			//!< Event handler for escape screen capture
			void GUISelectFrameOnClose(wxCloseEvent& event);

			//!< Redrawing window event handlers
			void OnBgPanelPaint(wxPaintEvent& event);

			//!< Event handlers for resizing
			void OnLeftDownForResizeFromUpperLeft(wxMouseEvent& event);
			void OnLeftDownForResizeFromUpperRight(wxMouseEvent& event);
			void OnLeftDownForResizeFromLowerLeft(wxMouseEvent& event);
			void OnLeftDownForResizeFromLowerRight(wxMouseEvent& event);

			

			void OnLeftUp(wxMouseEvent& event);
			void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
			void OnResizeTimer(wxTimerEvent& event);

			//!< Resizing helper functions
			void DoDragBasedResize();
			void StartResize(wxWindow* win, const wxPoint& p);
			void CompleteResize(bool doFinalResize = false);

			//!< Data and objects needed for resizing.
			RESIZE_MODE m_resizeMode;

			wxTimer m_resizeTimer;
			int m_resizeFrequency;
			int m_resizeAreaLength;
			
			wxPoint m_resizeStartPoint;
			wxSize m_initialFrameSize;
			wxPoint m_initialFramePosition;

			wxWindow* m_curResizeWindow;


			//!< Internal panel for implementing GUI controls
			wxPanel* m_bgPanel;

		public:
			//!< Tracking state of selecting screen area.
			std::atomic<bool>  atomic_b_croppingScreenIsRaised = false;
			std::atomic<bool>  atomic_b_croppingScreenIsCanceled = false;

			SelectPanel();
			~SelectPanel();
		};
	}
}
