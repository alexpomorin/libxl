#ifndef XL_UI_DIBRESIZERFILTER_H
#define XL_UI_DIBRESIZERFILTER_H
#include <math.h>
#include "../common.h"
XL_BEGIN
UI_BEGIN

class CGenericFilter
{
protected:
#define FILTER_PI  double (3.1415926535897932384626433832795)
#define FILTER_2PI double (2.0 * 3.1415926535897932384626433832795)
#define FILTER_4PI double (4.0 * 3.1415926535897932384626433832795)

	double  m_dWidth;

public:
    
	CGenericFilter (double dWidth) : m_dWidth (dWidth) {}
	virtual ~CGenericFilter () {}

	double GetWidth () { return m_dWidth; }
	void SetWidth (double dWidth) { m_dWidth = dWidth; }

	virtual double Filter (double dVal) = 0;
};

class CBoxFilter : public CGenericFilter
{
public:
	CBoxFilter () : CGenericFilter(0.5) {}
	virtual ~CBoxFilter () {}

	double Filter (double dVal) { return (fabs(dVal) <= m_dWidth ? 1.0 : 0.0); }
};

class CBilinearFilter : public CGenericFilter
{
public:
	CBilinearFilter () : CGenericFilter(1) {}
	virtual ~CBilinearFilter () {}

	double Filter (double dVal) {
		dVal = fabs(dVal); 
		return (dVal < m_dWidth ? m_dWidth - dVal : 0.0); 
	}
};


class CBicubicFilter : public CGenericFilter
{
protected:
	double p0, p2, p3;
	double q0, q1, q2, q3;

public:
	CBicubicFilter (double b = (1/(double)3), double c = (1/(double)3)) : CGenericFilter(2) {
		p0 = (6 - 2*b) / 6;
		p2 = (-18 + 12*b + 6*c) / 6;
		p3 = (12 - 9*b - 6*c) / 6;
		q0 = (8*b + 24*c) / 6;
		q1 = (-12*b - 48*c) / 6;
		q2 = (6*b + 30*c) / 6;
		q3 = (-b - 6*c) / 6;
	}
	virtual ~CBicubicFilter () {}

	double Filter (double dVal) { 
		dVal = fabs(dVal);
		if(dVal < 1) {
			return (p0 + dVal * dVal * (p2 + dVal * p3));
		} else if (dVal < 2) {
			return (q0 + dVal * (q1 + dVal * (q2 + dVal * q3)));
		}
		return 0;
	}
};

class CCatmullRomFilter : public CGenericFilter
{
public:
	CCatmullRomFilter () : CGenericFilter(2) {}
	virtual ~CCatmullRomFilter () {}

	double Filter (double dVal) { 
		if(dVal < -2) return 0;
		if(dVal < -1) return (0.5*(4 + dVal*(8 + dVal*(5 + dVal))));
		if(dVal < 0)  return (0.5*(2 + dVal*dVal*(-5 - 3*dVal)));
		if(dVal < 1)  return (0.5*(2 + dVal*dVal*(-5 + 3*dVal)));
		if(dVal < 2)  return (0.5*(4 + dVal*(-8 + dVal*(5 - dVal))));
		return 0;
	}
};

class CLanczos3Filter : public CGenericFilter
{
public:
	CLanczos3Filter () : CGenericFilter(3) {}
	virtual ~CLanczos3Filter () {}

	double Filter (double dVal) { 
		dVal = fabs(dVal); 
		if (dVal < m_dWidth)	{
			return (sinc(dVal) * sinc(dVal / m_dWidth));
		}
		return 0;
	}

private:
	double sinc (double value) {
		if (value != 0) {
			value *= FILTER_PI;
			return (sin(value) / value);
		} 
		return 1;
	}
};

class CBSplineFilter : public CGenericFilter
{
public:
	CBSplineFilter () : CGenericFilter(2) {}
	virtual ~CBSplineFilter () {}

	double Filter (double dVal) { 
		dVal = fabs(dVal);
		if (dVal < 1) {
			return (4 + dVal*dVal*(-6 + 3*dVal)) / 6;
		} else if (dVal < 2) {
			double t = 2 - dVal;
			return (t*t*t / 6);
		}
		return 0;
	}
};

class CBlackmanFilter : public CGenericFilter
{
public:
	CBlackmanFilter (double dWidth = double(0.5)) : CGenericFilter(dWidth) {}
	virtual ~CBlackmanFilter () {}

	double Filter (double dVal) {
		if (fabs (dVal) > m_dWidth) {
			return 0; 
		}
		double dN = 2 * m_dWidth + 1; 
		dVal /= (dN - 1);
		return 0.42 + 0.5 * cos(FILTER_2PI * dVal) + 0.08 * cos(FILTER_4PI * dVal); 
	}
};


UI_END
XL_END
#endif
