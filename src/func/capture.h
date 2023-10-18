/////////////////////////////////////////////////////////////////////////////
// Name:            capture.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         09/10/2023
// Last edit:       18/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once

//---------------------------------------------------------------------------
// CaptureMechanism
//---------------------------------------------------------------------------

//!< Definition of default delay time for the capturing process 
#define DEFAULT_DELAY 600

#include "wx/window.h"
#include "wx/bitmap.h"
#include "wx/display.h"
#include "wx/filename.h"
#include "wx/dcscreen.h"
#include "wx/dcmemory.h"
#include "wx/string.h"

#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>


namespace Func {
    /** Format IDs used for deciding which type of encoding to save file */
    enum Format {
        PNG = 0,
        JPEG = 1,
        BMP = 2,
        WEBP = 3
    };

    /** Naming IDs used for deciding which type of name to generate */
    enum Naming {
        Numeric = 0,
        Date = 1,
        Timestamp = 2,
        Empty = 3
    };

    /** Mode IDs used for deciding which mode to capture the screen */
    enum Mode {
        None = 0,
        Full = 1,
        Area = 2,
        Active = 3,
    };

    /** Result IDs used for return result of the capturing process */
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

    /** @class CaptureMechanism
    
        CaptureMechanism provides an easy-to-use and adjustable facility to
        take screenshots for all controls fully automatically and correctly.

        This class defines screen capturing functions and handing output
        saving.
    */
    class CaptureMechanism {
    
    private:
        //!< Container for the capturing image from screen
        wxBitmap bitmap_Saved;
        //!< Path leading to the saving directory
        wxString str_defaultDir;
        //!< Prefix string for the saving file
        wxString str_prefix;

        //!< Setting up for each mode of screen capturing
        void CapturingAllScreen(wxRect geomegy);
        void CapturingArea(wxRect geomegy);
        void CapturingActive(wxRect geomegy);

        //!< Processing grabbing image from screen
        void GrabbingScreenshot(wxRect geomegy, int delay);

        //!< Processing delaying time before grabbing
        void Delay(int miliseconds);

        //!< Processing exporing the output image
        void Save();

    public:
        //!< Fullscreen rendering rect's properties
        wxPoint pts_mostUpperLeftPosition;
        wxSize size_fullExtendedPhysicalDisplay;
        
        //!< Capturing mode
        Mode mode_captureType = Mode::None;

        //!< Displaying infos
        std::vector<DISPLAYINFO> infos_displayHandlers;

        CaptureMechanism();
        ~CaptureMechanism() { }
        
        //!< Capturing the screen
        void Capture(wxWindow* selectFrame);
    };
}