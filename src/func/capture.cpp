// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "capture.h"



// ----------------------------------------------------------------------------
// CaptureMechanism - Construction
// ----------------------------------------------------------------------------

Func::CaptureMechanism::CaptureMechanism() {
	// Get the primary display properties
	int primaryIndex = wxDisplay::GetFromPoint(wxPoint(0, 0));
	wxDisplay primaryDisplay(primaryIndex);
	pts_mostUpperLeftPosition = { 0, 0 };
	wxPoint pts_mostLowerRightPosition = {
		primaryDisplay.GetCurrentMode().GetWidth(),
		primaryDisplay.GetCurrentMode().GetHeight()
	};
	

	// Get the other display properties
	for (int i = 0; i < wxDisplay::GetCount(); i++) {
		wxDisplay display(i);
		wxRect screen = display.GetGeometry();
		infos_displayHandlers.push_back({
			wxPoint({screen.x, screen.y}),
			wxSize({screen.width, screen.height}),
			wxSize({display.GetCurrentMode().GetWidth(), 
				display.GetCurrentMode().GetHeight()})
		});
		if (i == primaryIndex) continue;
		// Get the full physical resolution
		pts_mostUpperLeftPosition.x = std::min(pts_mostUpperLeftPosition.x, screen.x);
		pts_mostUpperLeftPosition.y = std::min(pts_mostUpperLeftPosition.y, screen.y);

		pts_mostLowerRightPosition.x = std::max(pts_mostLowerRightPosition.x, 
										screen.x + display.GetCurrentMode().GetWidth());
		pts_mostLowerRightPosition.y = std::max(pts_mostLowerRightPosition.y,
										screen.y + display.GetCurrentMode().GetHeight());
	}

	size_fullExtendedPhysicalDisplay = {
		pts_mostLowerRightPosition.x - pts_mostUpperLeftPosition.x,
		pts_mostLowerRightPosition.y - pts_mostUpperLeftPosition.y
	};

	str_defaultDir = getenv("USERPROFILE");
	str_defaultDir += "\\Documents\\Screenshots";
	return;
}

Func::CaptureMechanism::~CaptureMechanism() {}

// ----------------------------------------------------------------------------
// CaptureMechanism - Functions
// ----------------------------------------------------------------------------

void Func::CaptureMechanism::CapturingAllScreen(const wxRect& geomegy) {
	str_prefix = "-screenshot-Full";
	GrabbingScreenshot(geomegy, DEFAULT_DELAY);
}

void Func::CaptureMechanism::CapturingArea(const wxRect& geomegy) {
	str_prefix = "-screenshot-Area";
	GrabbingScreenshot(geomegy, DEFAULT_DELAY);
}

void Func::CaptureMechanism::CapturingActive(const wxRect& geomegy) {
	str_prefix = "-screenshot-Active";
	GrabbingScreenshot(geomegy, DEFAULT_DELAY);
}

void Func::CaptureMechanism::GrabbingScreenshot(const wxRect& geomegy, int delay) {
	// Delaying before image grabbing
	if (delay) Delay(delay);
	// Create a DC for the whole screen area
	wxScreenDC dcScreen;
	// Create a memory DC that will be used for actually taking the screenshot
	wxMemoryDC dcCapture;
	bitmap_Saved.Create(
		geomegy.width, 
		geomegy.height,
		wxBITMAP_SCREEN_DEPTH
	);
	dcCapture.SelectObject(bitmap_Saved);
	dcCapture.Clear();

	// Blit the actual screen on the memory DC
	dcCapture.Blit(0, // Copy to this X coordinate
		0, // Copy to this Y coordinate
		geomegy.width, // Copy this width
		geomegy.height, // Copy this height
		&dcScreen, // From where do we copy?
		geomegy.x, // What's the X offset in the original DC?
		geomegy.y  // What's the Y offset in the original DC?
	);

	//// Select the Bitmap out of the memory DC
	dcScreen.Clear();
	dcCapture.SelectObject(wxNullBitmap);
	Save();
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

	wxFileName fullFileName(str_defaultDir,  fileName + str_prefix +
		"-" + wxPlatformInfo::Get().GetPortIdShortName() + ".png");

	// do not overwrite already existing files with this name
	while (fullFileName.FileExists())
		fullFileName.SetName(fullFileName.GetName() + "_");

	// save the screenshot as a PNG
	bitmap_Saved.SaveFile(fullFileName.GetFullPath(), wxBITMAP_TYPE_PNG);
}


void Func::CaptureMechanism::Capture(wxWindow* selectFrame) {
	// Processing fullscreen capture
	if (mode_captureType == Mode::Full) {
		CapturingAllScreen(selectFrame->GetScreenRect());
		mode_captureType = Mode::None;
		return;
	}

	// Converting logical coordinates to physical ones
	int displayIDx = wxDisplay::GetFromWindow(selectFrame);
	std::pair<double, double> pair_scaleFactors = {
		static_cast<double>(infos_displayHandlers[displayIDx].physicalResolution.x) /
				infos_displayHandlers[displayIDx].logicalResolution.x,
		static_cast<double>(infos_displayHandlers[displayIDx].physicalResolution.y) /
				infos_displayHandlers[displayIDx].logicalResolution.y
	};
	wxRect geo = selectFrame->GetScreenRect();
	wxRect physical_geo = wxRect(
		(geo.x - infos_displayHandlers[displayIDx].position.x) * pair_scaleFactors.first
			+ infos_displayHandlers[displayIDx].position.x,
		(geo.y - infos_displayHandlers[displayIDx].position.y) * pair_scaleFactors.second
			+ infos_displayHandlers[displayIDx].position.y,
		geo.width * pair_scaleFactors.first,
		geo.height * pair_scaleFactors.second
	);

	// Processing other captures
	if (mode_captureType == Mode::Area) {
		CapturingArea(physical_geo);
	}
	else if (mode_captureType == Mode::Active) {
		CapturingActive(physical_geo);
	}
	mode_captureType = Mode::None;
}
