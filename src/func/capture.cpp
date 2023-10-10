// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "capture.h"



// ----------------------------------------------------------------------------
// CaptureMechanism
// ----------------------------------------------------------------------------

Func::CaptureMechanism::CaptureMechanism() {
	wxScreenDC dcScreen;
	dcScreen.GetSize(&n_displayWidth, &n_displayHeight);
	return;
}

void Func::CaptureMechanism::CapturingAllScreen() {
	Capturing(DEFAULT_DELAY);
	Save("AAAAAA");
}


void Func::CaptureMechanism::CapturingArea() {

}

void Func::CaptureMechanism::CapturingActive() {

}

void Func::CaptureMechanism::Capturing(int delay) {
#ifdef __WXMAC__

#else
	if (delay) Delay(delay);
	free(m_bitmap_Buffer);
	m_bitmap_Buffer = new wxBitmap();
	m_bitmap_Buffer->Create(n_displayWidth, n_displayWidth);

	// Create a DC for the whole screen area
	wxScreenDC dcScreen;
	dcScreen.GetSize(&n_displayWidth, &n_displayHeight);
	m_bitmap_Buffer = new wxBitmap (n_displayWidth, n_displayHeight, -1);
	// Create a memory DC that will be used for actually taking the screenshot
	wxMemoryDC memDC;
	memDC.SelectObject(*m_bitmap_Buffer);
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

void Func::CaptureMechanism::Cropping(int x, int y, int width, int height) {
	wxBitmap m_tmpBitmap = m_bitmap_Buffer->GetSubBitmap(wxRect(wxPoint(x, y), wxSize(width, height)));
	free(m_bitmap_Buffer);
	m_bitmap_Buffer = &m_tmpBitmap;
	Save("AAAAAA");
}

void Func::CaptureMechanism::Union() {

}

void Func::CaptureMechanism::Delay(int seconds) {
	clock_t start = clock();
	while (clock() - start < (clock_t)CLOCKS_PER_SEC * seconds)
		wxYieldIfNeeded();
}

void Func::CaptureMechanism::Save(const wxString& fileName) {
	// make sure default_dir exists
	if (!wxDirExists(str_defaultDir))
		wxMkdir(str_defaultDir);

	wxFileName fullFileName(str_defaultDir, "appear-" + fileName +
		"-" + wxPlatformInfo::Get().GetPortIdShortName() + ".png");

	// do not overwrite already existing files with this name
	while (fullFileName.FileExists())
		fullFileName.SetName(fullFileName.GetName() + "_");

	// save the screenshot as a PNG
	m_bitmap_Buffer->SaveFile(fullFileName.GetFullPath(), wxBITMAP_TYPE_PNG);
	free(m_bitmap_Buffer);
}

void Func::CaptureMechanism::InitiatingRegionSelection() {
	Capturing(DEFAULT_DELAY);
}

void Func::CaptureMechanism::GrabbingImage() {
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