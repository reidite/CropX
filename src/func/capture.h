/////////////////////////////////////////////////////////////////////////////
// Name:            capture.cpp
// Purpose:         Initialize the entry point of the program
// Author:          Vincent Nguyen
// Maintainer:      Vincent Nguyen
// Contributors:    N/A
// Created:         09/10/2023
// Last edit:       09/10/2023
// Copyright:       Anyone
// Licence:         GPL-3.0 license
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "wx/bitmap.h"
#include "wx/filename.h"
#include "wx/notebook.h"
#include "wx/dcscreen.h"
#include "wx/dcmemory.h"
#include "wx/string.h"
#include <vector>

#include "wx/gdicmn.h"

//!< Definition of default delay time for the capturing process 
#define DEFAULT_DELAY 3

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

    class CaptureMechanism
    {
    private:
        wxCoord n_displayWidth, n_displayHeight;
        wxString str_defaultDir = "C:/Users/ATOMI-User/Documents/Screenshots";

        wxBitmap* m_bitmap_Buffer;

        void CapturingAllScreen();
        void CapturingArea();
        void CapturingActive();
        void Capturing(int x, int y, int width, int height, int delay);
        void Union();
        void Delay(int seconds);
        void Save(const wxString& fileName);

    public:
        Mode mode = Mode::None;
        CaptureMechanism();

        ~CaptureMechanism() { }

        void GrabbingImage() {
            switch (mode) {
            case Mode::Full:
                CapturingAllScreen();
                break;
            case Mode::Area:
                CapturingArea();
                break;
            case Mode::Active:
                CapturingActive();
                break;
            default:
                break;
            }
        }
    };
}