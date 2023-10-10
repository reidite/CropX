#include "SelectPanel.h"

UI::Custom::SelectPanel::SelectPanel()
	: GUISelectFrame(nullptr, wxID_ANY, wxString(""), wxDefaultPosition, wxDefaultSize) {

}

void UI::Custom::SelectPanel::GUISelectFrameOnClose(wxCloseEvent& event) {
	atomic_b_croppingScreenIsRaised = true;
}