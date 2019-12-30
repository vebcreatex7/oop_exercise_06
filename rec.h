#pragma once

#include "point.h"
#include "stack.h"
#include <cassert>

template <class T>
struct TRectangle {
	TPoint<T> a, b, c, d;
	TRectangle();
	TRectangle(std::istream&);
	double Square() const;
	TPoint<T> Center() const;
	void Print() const;
};


template <class T>
TRectangle<T>::TRectangle() {}
template <class T>
TRectangle<T>::TRectangle(std::istream& is) {
	is >> a >> b >> c >> d;
	TPoint<T> ab, ad, cb, cd;
	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ad.x = d.x - a.x;
	ad.y = d.y - a.y;
	cb.x = b.x - c.x;
	cb.y = b.y - c.y;
	cd.x = d.x - c.x;
	cd.y = d.y - c.y;
	if (acos((ab.x * ad.x + ab.y * ad.y) / (sqrt(ab.x * ab.x + ab.y * ab.y) * sqrt(ad.x * ad.x + ad.y * ad.y))) / M_PI != 0.5 || acos((cb.x * cd.x + cb.y * cd.y) / (sqrt(cb.x * cb.x + cb.y * cb.y) * sqrt(cd.x * cd.x + cd.y * cd.y))) / M_PI != 0.5) {
		throw std::logic_error("it's not rectangle\n");
	}
}

template <class T>
double TRectangle<T>::Square() const {
	double ans = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return fabs(ans);
}

template <class T>
TPoint<T> TRectangle<T>::Center() const {
	TPoint<T> p;
	T x = (a.x + b.x + c.x + d.x) /4;
	T y = (a.y + b.y + c.y + d.y) /4;
	p.x = x;
	p.y = y;
	
	return p;
}

template <class T>
void TRectangle<T>::Print() const {
	std::cout << a << b << c << d << "\n";
}
