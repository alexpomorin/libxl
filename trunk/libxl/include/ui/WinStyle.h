#ifndef XL_UI_WINSTYLE_H
#define XL_UI_WINSTYLE_H
#include <limits>
#include "../common.h"
#include "../string.h"

#ifdef max // <windows.h> defines max & min
#define RESTORE_MIN_MAX
#pragma push_macro ("min")
#pragma push_macro ("max")
#undef max
#undef min
#endif


namespace xl {
	namespace ui {



const int SIZE_FILL = -1;
const int EDGE_AUTO = std::numeric_limits<int>::max();

/**
 *  edge type
 */
enum EDGETYPE {
	ET_TOP,
	ET_RIGHT,
	ET_BOTTOM,
	ET_LEFT,
	ET_ALL,
	ET_COUNT = ET_ALL
};

/**
 * edge, used by margin or padding, and so on
 */
struct EDGE {
	int top;
	int right;
	int bottom;
	int left;

	EDGE (int t = 0, int r = 0, int b = 0, int l = 0)
		: top(t), right(r), bottom(b), left(l) {}
	int width () const {
		return (left == EDGE_AUTO ? 0 : left) + (right == EDGE_AUTO ? 0 : right);
	}
	int height () const {
		return (top == EDGE_AUTO ? 0 : top) + (bottom == EDGE_AUTO ? 0 : bottom);
	}
};

struct BORDEREDGE {
	int width;
	COLORREF color;
	uint style; // not used now

	BORDEREDGE () {
		reset();
	}

	void reset () {
		width = 0;
		color = RGB(0,0,0);
		style = 0;
	}
};

struct BORDER {
	BORDEREDGE top;
	BORDEREDGE right;
	BORDEREDGE bottom;
	BORDEREDGE left;

	void reset ();
	void setWidth (int width, EDGETYPE et = ET_ALL);
	void setColor (COLORREF color, EDGETYPE et = ET_ALL);
	int width () const { return left.width + right.width; }
	int height () const { return top.width + bottom.width; }
};

enum BACKGROUNDTYPE {
	BGT_NONE,
	BGT_RGB,
	BGT_IMAGE_ID,
	BGT_IMAGE_URL,
	BGT_COUNT
};

struct BACKGROUND {
	BACKGROUNDTYPE type;
	
};


enum POSITION_X {
	PX_LEFT,
	PX_RIGHT,
	PX_COUNT
};

enum POSITION_Y {
	PY_TOP,
	PY_BOTTOM,
	PY_COUNT
};

enum FONTWEIGHT {
	FONTW_NORMAL,
	FONTW_BOLD,
	FONTW_COUNT
};


class CWinStyle {
protected:
	void _ParseEdge (tstring value, EDGE &edge);
	COLORREF _ParseColor (tstring value);
	void _ParseBorder (tstring key, tstring value);
	void _Reset ();
	void _SetStyle (const tstring &style, bool &relayout, bool &redraw);

	/**
	 * the derived class can have its own _ParseProperty()
	 */
	virtual void _ParseProperty (const tstring &key, const tstring &value, bool &relayout, bool &redraw);

public:
	bool display;
	bool disable;
	bool isfloat;

	EDGE margin;
	EDGE padding;
	BORDER border;

	POSITION_X px;
	POSITION_Y py;

	int width;
	int height;

	FONTWEIGHT fontweight;
	COLORREF color;
	int opacity; // alpha = 100 - opacity

	CWinStyle ();
	virtual ~CWinStyle ();
};




	} // ui
} // xl

#ifdef RESTORE_MIN_MAX
#pragma pop_macro ("min")
#pragma pop_macro ("max")
#undef RESTORE_MIN_MAX
#endif

#endif
