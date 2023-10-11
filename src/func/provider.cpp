#include "Provider.h"

Func::Provider::Provider() {
	while (FAILED(CoInitialize(NULL)));
	while (FAILED(CoCreateInstance(__uuidof(CUIAutomation8), NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_automation))));
}

HRESULT Func::Provider::GetActiveComponent(int x, int y) {
	POINT pt = { x, y };
	while (FAILED(m_automation->ElementFromPoint(pt, &element)));
	VARIANT varValue;
	if (SUCCEEDED(element->GetCurrentPropertyValue(UIA_BoundingRectanglePropertyId, &varValue))) {
		double* pData;
		SafeArrayAccessData(varValue.parray, (void**)&pData);
		n_x = static_cast<unsigned int>(pData[0]);
		n_y = static_cast<unsigned int>(pData[1]);
		width = static_cast<unsigned int>(pData[2]);
		height = static_cast<unsigned int>(pData[3]);
		return true;
	}
	return false;
}