#include "SelectPanel.h"

UI::Custom::SelectPanel::SelectPanel()
	: GUISelectFrame(nullptr, wxID_ANY, wxString(""), wxDefaultPosition, wxDefaultSize) {

}

void UI::Custom::SelectPanel::GUISelectFrameOnClose(wxCloseEvent& event) {
	atomic_b_croppingScreenIsRaised = true;
}

void UI::Custom::SelectPanel::OnPaint(wxPaintEvent &event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxPoint pos = this->GetPosition();
	wxSize size = this->GetVirtualSize();

	std::vector<wxPoint> points = { wxPoint(pos.x, pos.y), 
							wxPoint(pos.x + size.x, pos.y), 
							wxPoint(pos.x + size.x, pos.y + size.y),
							wxPoint(pos.x, pos.y )};
	dc.SetPen(wxPen(wxColor(255, 255, 255)));
	dc.SetBrush(wxBrush(wxColor(255, 0, 255)));
	wxPointList ptsList;
	dc.DrawLines(points.size(), &points[0], 0, 0);
}