#ifndef XL_UI_CTRLBASE_H
#define XL_UI_CTRLBASE_H
#include <atlbase.h>
#include <atltypes.h>
#include <atlapp.h>
#include <atltypes.h>
#include "../../include/common.h"
#include "WinStyle.h"

namespace xl {
	namespace ui {

class CCtrlBase	: public WinStyle
{
protected:
	CRect m_rc; // it real position & size (not include margin, but include padding)

public:
	COLORREF m_clrBackground;

	CCtrlBase ();
	virtual ~CCtrlBase ();

	virtual void draw (HDC hdc);
	void setRect (CRect rc);
};

	} // namespace ui
} // namespace xl

#endif