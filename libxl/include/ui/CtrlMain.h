#ifndef XL_UI_CTRL_MGR_H
#define XL_UI_CTRL_MGR_H
#include <vector>
#include <atlbase.h>
#include <atlwin.h>
#include "Control.h"
#include "CtrlGesture.h"


namespace xl {
	namespace ui {

class CCtrlMain : public CControl
{
	friend class CControl;

protected:
	ATL::CWindow         *m_pWindow;

	/**
	 * inner properties
	 */
	bool m_captured;
	CControlPtr m_ctrlHover;
	CControlPtr m_ctrlCapture;
	CCtrlGesturePtr m_ctrlGesture;
	mutable CRect m_rcLayout; // save the rect passed by this->layout(rc), used by reLayout()

	//////////////////////////////////////////////////////////////////////////
	// protected methods
	bool _SetCapture (CControlPtr ctrl);
	void _SetHoverCtrl (CControlPtr ctrlHover, CPoint pt);

	//////////////////////////////////////////////////////////////////////////
	// virtual protected methods
	virtual CCtrlMain* _GetMainCtrl () { return this; }

public:
	CCtrlMain (ATL::CWindow *, CCtrlTargetRawPtr target);
	virtual ~CCtrlMain ();
	void enableGesture (bool enable);

	void invalidateControl (CControlPtr ctrl = CControlPtr()) const;
	void reLayout () const;
	CControlPtr getHoverCtrl () { return m_ctrlHover; }
	CControlPtr getCaptureCtrl () { return m_ctrlCapture; }
	CControlPtr getGestureCtrl () { return m_ctrlGesture; }

	virtual CRect layout (CRect rc) const;

	BEGIN_MSG_MAP(CCtrlMain)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkGnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

typedef std::tr1::shared_ptr<CCtrlMain>        CCtrlMainPtr;


	} // ui
} // xl


#endif
