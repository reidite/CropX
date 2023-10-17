// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "capture.h"



// ----------------------------------------------------------------------------
// CaptureMechanism
// ----------------------------------------------------------------------------

Func::CaptureMechanism::CaptureMechanism() {
	// Get the primary display
	int primaryIndex = wxDisplay::GetFromPoint(wxPoint(0, 0));
	wxDisplay primaryDisplay(primaryIndex);
	size_fullExtendedLogicalDisplay = { 
		primaryDisplay.GetGeometry().width,
		primaryDisplay.GetGeometry().height
	};
	size_fullExtendedPhysicalDisplay = { 
		primaryDisplay.GetCurrentMode().GetWidth(),
		primaryDisplay.GetCurrentMode().GetHeight()
	};
	for (int i = 0; i < wxDisplay::GetCount(); i++) {
		wxDisplay display(i);
		wxRect screen = display.GetGeometry();
		infos_displayHandlers.push_back({
			wxPoint({screen.x, screen.y}),
			wxSize({screen.width, screen.height}),
			wxSize({display.GetCurrentMode().GetWidth(), 
				display.GetCurrentMode().GetHeight()})
		});
		if (i != primaryIndex) {
			if (screen.x >= size_fullExtendedPhysicalDisplay.x) {
				size_fullExtendedLogicalDisplay.x += 
					primaryDisplay.GetGeometry().width;
				size_fullExtendedPhysicalDisplay.x += 
					primaryDisplay.GetCurrentMode().GetWidth();
			}
			if (screen.y >= size_fullExtendedPhysicalDisplay.y) {
				size_fullExtendedLogicalDisplay.y += 
					primaryDisplay.GetGeometry().height;
				size_fullExtendedPhysicalDisplay.y += 
					primaryDisplay.GetCurrentMode().GetHeight();
			}
		}

	}

	bitmap_Display.Create(size_fullExtendedLogicalDisplay.x,
		size_fullExtendedLogicalDisplay.y,
		wxBITMAP_SCREEN_DEPTH);

	bitmap_Buffer.Create(size_fullExtendedPhysicalDisplay.x,
		size_fullExtendedPhysicalDisplay.y,
		wxBITMAP_SCREEN_DEPTH);

	pair_scaleFactors = {
		static_cast<double>(size_fullExtendedPhysicalDisplay.x) / 
									size_fullExtendedLogicalDisplay.x,
		static_cast<double>(size_fullExtendedPhysicalDisplay.y) / 
									size_fullExtendedLogicalDisplay.y
	};

	str_defaultDir = getenv("USERPROFILE");
	str_defaultDir += "\\Documents\\Screenshots";
	return;
}


void Func::CaptureMechanism::CapturingAllScreen(wxWindow* selectFrame) {
	GrabbingScreenshot(DEFAULT_DELAY);
	Crop(selectFrame->GetScreenRect());
}


void Func::CaptureMechanism::CapturingArea(wxWindow* selectFrame) {
	GrabbingScreenshotWithDPI(DEFAULT_DELAY);
}

void Func::CaptureMechanism::CapturingActive(wxWindow* selectFrame) {
	GrabbingScreenshot(DEFAULT_DELAY);
}

void Func::CaptureMechanism::GrabbingScreenshot(int delay) {
#ifdef _WIN32
	//windows code goes here
	if (delay) Delay(delay);

	// Create a DC for the whole screen area
	wxScreenDC dcScreen;
	// Create a memory DC that will be used for actually taking the screenshot
	wxMemoryDC dcCapture;
	dcCapture.SelectObject(bitmap_Buffer);
	dcCapture.Clear();

	// Blit the actual screen on the memory DC
	dcCapture.Blit(0, // Copy to this X coordinate
		0, // Copy to this Y coordinate
		size_fullExtendedPhysicalDisplay.x, // Copy this width
		size_fullExtendedPhysicalDisplay.y, // Copy this height
		&dcScreen, // From where do we copy?
		0, // What's the X offset in the original DC?
		0  // What's the Y offset in the original DC?
	);

	//// Select the Bitmap out of the memory DC
	dcCapture.SelectObject(wxNullBitmap);
#elif __linux__
	//linux  code goes here

#elif __WXMAC__
	//mac code goes here

#else

#endif

}

void Func::CaptureMechanism::GrabbingScreenshotWithDPI(int delay) {
#ifdef _WIN32
	//windows code goes here
	if (delay) Delay(delay);

	// Create a DC for the whole screen area
	wxScreenDC dcScreen;
	// Create a memory DC that will be used for actually taking the screenshot
	wxMemoryDC dcCapture;
	dcCapture.SelectObject(bitmap_Buffer);
	dcCapture.Clear();

	// Blit the actual screen on the memory DC
	dcCapture.Blit(0, // Copy to this X coordinate
		0, // Copy to this Y coordinate
		size_fullExtendedPhysicalDisplay.x, // Copy this width
		size_fullExtendedPhysicalDisplay.y, // Copy this height
		&dcScreen, // From where do we copy?
		0, // What's the X offset in the original DC?
		0  // What's the Y offset in the original DC?
	);

	// Create a memory DC for taking the scaled displaying image
	dcCapture.SelectObject(bitmap_Display);
	dcCapture.StretchBlit(
		wxPoint(0, 0),
		size_fullExtendedLogicalDisplay,
		&dcScreen,
		wxPoint(0, 0),
		size_fullExtendedPhysicalDisplay
	);

	//// Select the Bitmap out of the memory DC
	dcCapture.SelectObject(wxNullBitmap);
	dcScreen.Clear();
#elif __linux__
	//linux  code goes here

#elif __WXMAC__
	//mac code goes here

#else

#endif

}

void Func::CaptureMechanism::Union() {

}

void Func::CaptureMechanism::Delay(int miliseconds) {
	clock_t start = clock();
	while (clock() - start < (clock_t) miliseconds)
		wxYieldIfNeeded();
}

void Func::CaptureMechanism::Save() {
	// setup the filename
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

	const wxString fileName(oss.str());

	// make sure default_dir exists
	if (!wxDirExists(str_defaultDir))
		wxMkdir(str_defaultDir);

	wxFileName fullFileName(str_defaultDir, "screenshot-" + fileName +
		"-" + wxPlatformInfo::Get().GetPortIdShortName() + ".png");

	// do not overwrite already existing files with this name
	while (fullFileName.FileExists())
		fullFileName.SetName(fullFileName.GetName() + "_");

	// save the screenshot as a PNG
	bitmap_Saved.SaveFile(fullFileName.GetFullPath(), wxBITMAP_TYPE_PNG);
	bitmap_Saved.FreeResource(true);
}

void Func::CaptureMechanism::Crop(wxRect geo) {
	wxRect physical_geo = wxRect(
		geo.x * pair_scaleFactors.first,
		geo.y * pair_scaleFactors.second,
		geo.width * pair_scaleFactors.first,
		geo.height * pair_scaleFactors.second
	);
	bitmap_Saved = bitmap_Buffer.GetSubBitmap(physical_geo);
	Save();
}

void Func::CaptureMechanism::Capture(wxWindow* selectFrame) {
	switch (mode_captureType) {
	case Mode::Full:
		CapturingAllScreen(selectFrame);
		break;
	case Mode::Area:
		CapturingArea(selectFrame);
		break;
	case Mode::Active:
		CapturingActive(selectFrame);
		break;
	default:
		break;
	}
	mode_captureType = Mode::None;
}
