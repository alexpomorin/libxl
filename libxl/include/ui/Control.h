#ifndef XL_UI_CONTROL_H
#define XL_UI_CONTROL_H
#include <memory>
#include <vector>
#include <atlbase.h>
#include <atltypes.h>
#include <atlapp.h>
#include "WinStyle.h"

XL_BEGIN
UI_BEGIN

//////////////////////////////////////////////////////////////////////////
// forward prototypes
class CCtrlMain;
class CCtrlTarget;

//////////////////////////////////////////////////////////////////////////
// typedef(s)
class CControl;
typedef std::tr1::shared_ptr<CControl>                 CControlPtr;
typedef std::tr1::weak_ptr<CControl>                   CControlWeakPtr;
typedef CControl                                      *CControlRawPtr;

typedef std::tr1::shared_ptr<CCtrlTarget>              CCtrlTargetPtr;
typedef CCtrlTarget                                   *CCtrlTargetRawPtr;

//////////////////////////////////////////////////////////////////////////
// consts

// used in onXXX for mouse event
const uint KP_CONTROL = 0x0001;
const uint KP_LBUTTON = 0x0002;
const uint KP_MBUTTON = 0x0004;
const uint KP_RBUTTON = 0x0008;
const uint KP_SHIFT   = 0x0010;


//////////////////////////////////////////////////////////////////////////
// CControl
class CControl : public CWinStyle
               , public std::tr1::enable_shared_from_this<CControl>
{
protected:
	friend class CCtrlMain;
	typedef std::vector<CControlPtr>               CControlContainer;
	typedef CControlContainer::iterator            CControlIter;
	typedef CControlContainer::const_iterator      CControlConstIter;
	typedef CControlContainer::reverse_iterator    CControlIterR;

	uint               m_id;

	CControlWeakPtr    m_parent;
	CControlContainer  m_controls;
	CRect              m_rect;

	void _LayoutChildren ();

	void _SetParent (CControlPtr parent);
	// void _SetTarget (CCtrlTargetRawPtr target);
	virtual CCtrlTargetRawPtr _GetTarget ();

	COLORREF _GetColor ();
	HFONT _GetFont ();
	void _DrawBorder (HDC hdc);
	void _DrawBackground (HDC hdc);

	bool _Capture (bool capture);
	uint _SetTimer (uint elapse, uint id = 0);

	//////////////////////////////////////////////////////////////////////////
	// virtual protected methods
	virtual CCtrlMain* _GetMainCtrl ();

public:
	CControl (uint id = 0);
	virtual ~CControl ();

	uint getID () const { return m_id; }
	CRect getClientRect () const; // exclude the border and padding

	bool insertChild (CControlPtr child);
	bool isChild (CControlPtr control);
	CControlPtr removeChild (uint id);
	CControlPtr getControlByID (uint id);
	CControlPtr getControlByPoint (CPoint pt);
	void invalidate ();

	void resetStyle ();
	void setStyle (const tstring &style);
	void setOpacity (int opacity);


	//////////////////////////////////////////////////////////////////////////
	// virtual
	virtual CRect layout (CRect rc);
	virtual bool isPointIn (CPoint pt) const;
	virtual bool isCursorIn ();
	virtual void draw (HDC hdc, CRect rcClip);
	virtual void drawMe (HDC hdc);

	virtual void onAttach () {} // called only when attached to CCtrlMain (no matter directly or not)
	virtual void onDetach () {} // called only when detached from CCtrlMain (no matter directly or not)

	virtual void onSize () {}
	virtual void onMouseIn (CPoint /*pt*/) {} // called when mouse moved in
	virtual void onMouseInChild (CPoint /*pt*/) {} // called when mouse moved in some child
	virtual void onMouseOut (CPoint /*pt*/) {} // called when mouse moved out (note maybe in its children)
	virtual void onMouseOutChild (CPoint /*pt*/) {} // called when mouse moved out its child
	virtual void onMouseMove (CPoint /*pt*/, xl::uint /*key*/) {} // called when mouse moved (in or has capture)
	virtual void onLButtonDown (CPoint /*pt*/, xl::uint /*key*/) {}
	virtual void onLButtonUp (CPoint /*pt*/, xl::uint /*key*/) {}
	virtual void onRButtonDown (CPoint /*pt*/, xl::uint /*key*/) {}
	virtual void onRButtonUp (CPoint /*pt*/, xl::uint /*key*/) {}
	virtual void onMouseWheel (CPoint /*pt*/, int /*delta*/, xl::uint /*key*/) {}
	virtual void onLostCapture () {} // called only when lost capture CAUSED BY SYSTEM
	virtual void onTimer (xl::uint /*id*/) {}
};

UI_END
XL_END
#endif
