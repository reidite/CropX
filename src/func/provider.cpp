#include "Provider.h"

// ----------------------------------------------------------------------------
// CaptureMechanism - Construction
// ----------------------------------------------------------------------------

Func::Provider::Provider() {
	while (FAILED(CoInitialize(NULL)));
	while (FAILED(CoCreateInstance(__uuidof(CUIAutomation), NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_automation))));
	m_automation->get_ControlViewWalker(&walker);
}

// ----------------------------------------------------------------------------
// CaptureMechanism - Functions
// ----------------------------------------------------------------------------

HRESULT Func::Provider::GetActiveComponent(int cursor_x, int cursor_y) {
	POINT pt = { cursor_x, cursor_y };
	while (FAILED(m_automation->ElementFromPoint(pt, &element)));
	VARIANT varValue;
	if (SUCCEEDED(element->GetCurrentPropertyValue(UIA_BoundingRectanglePropertyId, &varValue))) {
		double* pData;
		SafeArrayAccessData(varValue.parray, (void**)&pData);
		x = static_cast<unsigned int>(pData[0]);
		y = static_cast<unsigned int>(pData[1]);
		width = static_cast<unsigned int>(pData[2]);
		height = static_cast<unsigned int>(pData[3]);
		
		if (FAILED(walker->GetParentElement(element, &parent)) || !parent) return true;

		if (SUCCEEDED(parent->GetCurrentPropertyValue(UIA_BoundingRectanglePropertyId, &varValue))) {
			SafeArrayAccessData(varValue.parray, (void**)&pData);
			if (width > static_cast<unsigned int>(pData[2]) ||
				height > static_cast<unsigned int>(pData[3])) {
				x = static_cast<unsigned int>(pData[0]);
				y = static_cast<unsigned int>(pData[1]);
				width = static_cast<unsigned int>(pData[2]);
				height = static_cast<unsigned int>(pData[3]);
			}
		}
		element->Release();
		parent->Release();

		return true;
	}
	return false;
}