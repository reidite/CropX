// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "capture.h"



// ----------------------------------------------------------------------------
// CaptureMechanism
// ----------------------------------------------------------------------------

Func::CaptureMechanism::CaptureMechanism() {
	wxScreenDC dcScreen;
	dcScreen.GetSize(&n_displayWidth, &n_displayHeight);
	
	m_bitmap_Buffer.Create(n_displayWidth, n_displayHeight, -1);

	str_defaultDir = getenv("USERPROFILE");
	str_defaultDir += "\\Documents\\Screenshots";
	return;
}


void Func::CaptureMechanism::CapturingAllScreen() {
	GrabbingScreenshot(DEFAULT_DELAY);
	Crop(0, 0, n_displayWidth, n_displayHeight);
}


void Func::CaptureMechanism::CapturingArea() {
	GrabbingScreenshot(DEFAULT_DELAY);
}

void Func::CaptureMechanism::CapturingActive() {
	GrabbingScreenshot(DEFAULT_DELAY);
}

void Func::CaptureMechanism::GrabbingScreenshot(int delay) {
#ifdef __WXMAC__

#else
	if (delay) Delay(delay);
	
	// Create a DC for the whole screen area
	wxScreenDC dcScreen;
	dcScreen.GetSize(&n_displayWidth, &n_displayHeight);
	// Create a memory DC that will be used for actually taking the screenshot
	wxMemoryDC memDC;
	memDC.SelectObject(m_bitmap_Buffer);
	memDC.Clear();

	// Blit the actual screen on the memory DC
	memDC.Blit(0, // Copy to this X coordinate
		0, // Copy to this Y coordinate
		n_displayWidth, // Copy this width
		n_displayWidth, // Copy this height
		&dcScreen, // From where do we copy?
		0, // What's the X offset in the original DC?
		0  // What's the Y offset in the original DC?
	);

	//// Select the Bitmap out of the memory DC
	memDC.SelectObject(wxNullBitmap);
#endif __WXMAC__
}

void Func::CaptureMechanism::Crop(int x, int y, int width, int height) {
	m_bitmap_Saved = m_bitmap_Buffer.GetSubBitmap(wxRect(wxPoint(x, y), wxSize(width, height)));
	Save();
}

void Func::CaptureMechanism::Union() {

}

void Func::CaptureMechanism::Delay(int seconds) {
	clock_t start = clock();
	while (clock() - start < (clock_t)CLOCKS_PER_SEC * seconds)
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
	m_bitmap_Saved.SaveFile(fullFileName.GetFullPath(), wxBITMAP_TYPE_PNG);
	m_bitmap_Saved.FreeResource(true);
}

void Func::CaptureMechanism::Capture() {
	switch (m_capturingMode) {
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