#ifndef XL_UI_CTRL_BUTTON_H
#define XL_UI_CTRL_BUTTON_H
#include "../common.h"
#include "Control.h"

namespace xl {
	namespace ui {

class CCtrlButton : public CControl 
{
protected:
	bool m_hover;
	bool m_push;

public:
	CCtrlButton (uint id);
	virtual ~CCtrlButton ();

	//////////////////////////////////////////////////////////////////////////
	// virtual methods
	virtual void drawMe (HDC hdc);

	virtual void onMouseIn (CPoint pt);
	virtual void onMouseOut (CPoint pt);
	virtual void onLostCapture();
	virtual void onLButtonDown (CPoint pt);
	virtual void onLButtonUp (CPoint pt);

	//////////////////////////////////////////////////////////////////////////
	// virtual button methods
	virtual void drawNormal (HDC hdc);
	virtual void drawHover (HDC hdc);
	virtual void drawPush (HDC hdc);
};


	} // ui
} // xl


#endif
