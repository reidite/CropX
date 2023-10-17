/////////////////////////////////////////////////////////////////////////////
// Name:            capture.cpp
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
#include "wx/window.h"
#include "wx/bitmap.h"
#include "wx/display.h"
#include "wx/filename.h"
#include "wx/dcscreen.h"
#include "wx/dcmemory.h"
#include "wx/string.h"
#include <wx/dcgraph.h>

#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>


#include "shlobj_core.h"
#include "shellscalingapi.h"
#include "uiautomationcore.h"

#include "wx/gdicmn.h"

//!< Definition of default delay time for the capturing process 
#define DEFAULT_DELAY 600

namespace Func {
    enum Format {
        PNG = 0,
        JPEG = 1,
        BMP = 2,
        WEBP = 3
    };

    enum Naming {
        Numeric = 0,
        Date = 1,
        Timestamp = 2,
        Empty = 3
    };

    enum Mode {
        None = 0,
        Full = 1,
        Area = 2,
        Active = 3,
    };

    enum Result {
        Failure = 0,
        Success = 1,
        Cancel = 2
    };

    struct DISPLAYINFO {
        wxPoint position;
        wxSize logicalResolution;
        wxSize physicalResolution;
    };

    class CaptureMechanism
    {
    private:
        wxString str_defaultDir;
        wxString str_prefix;
        void CapturingAllScreen(wxRect geomegy);
        void CapturingArea(wxRect geomegy);
        void CapturingActive(wxRect geomegy);

        void GrabbingScreenshot(wxRect geomegy, int delay);

        void Union();
        void Delay(int miliseconds);
        void Save();

    public:
        wxBitmap* bitmap_Saved;

        wxPoint pts_mostUpperLeftPosition;
        wxSize size_fullExtendedPhysicalDisplay;
        

        Mode mode_captureType = Mode::None;

        std::vector<DISPLAYINFO> infos_displayHandlers;

        CaptureMechanism();

        ~CaptureMechanism() { }
        
        void Capture(wxWindow* selectFrame);

    };
}