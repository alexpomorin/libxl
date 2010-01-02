#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../libxl/include/ui/MainWindow.h"


class CMainWindow : public xl::ui::CMainWindowT<CMainWindow>
{
public:
	DECLARE_WND_CLASS_EX (_T("CMainWindow"), 0, COLOR_INFOBK)
	BEGIN_MSG_MAP (CMainWindow)
		MESSAGE_HANDLER (WM_CREATE, OnCreate)
		MESSAGE_HANDLER (WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(CMainWindowT)
	END_MSG_MAP ()

	LRESULT OnCreate (UINT msg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnPaint (UINT msg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
};

#endif
