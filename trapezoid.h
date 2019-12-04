#ifndef TRAPEZOID_H
#define TRAPEZOID_H 1


#include "point.h"
#include <cassert>
#include <exception>

template <class T>
struct TTrapezoid {
	TPoint<T> a, b, c, d;
	TTrapezoid(std::istream&);
	TTrapezoid();
	double Square() const;
	TPoint<T> Center() const;
	void Print() const;
};

template <class T>
TTrapezoid<T>::TTrapezoid() {}

template <class T>
TTrapezoid<T>::TTrapezoid(std::istream& is) {
	is >> a >> b >> c >> d;
	TPoint<T> ab, ad, bc, dc;
	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ad.x = d.x - a.x;
	ad.y = d.y - a.y;
	bc.x = c.x - b.x;
	bc.y = c.y - b.y;
	dc.x = c.x - d.x;
	dc.y = c.y - d.y;
	if (acos((ab.x * dc.x + ab.y * dc.y) / (sqrt(ab.x * ab.x + ab.y * ab.y) * sqrt(dc.x * dc.x + dc.y * dc.y))) != 0 && acos((ad.x * bc.x + ad.y * bc.y) / (sqrt(ad.x * ad.x + ad.y * ad.y) * sqrt(bc.x * bc.x + bc.y * bc.y))) != 0) {
		throw std::logic_error("It's not a trapezoid\n");
	}
	//assert(acos((ab.x * dc.x + ab.y * dc.y) / (sqrt(ab.x * ab.x + ab.y * ab.y) * sqrt(dc.x * dc.x + dc.y * dc.y))) == 0 || acos((ad.x * bc.x + ad.y * bc.y) / (sqrt(ad.x * ad.x + ad.y * ad.y) * sqrt(bc.x * bc.x + bc.y * bc.y))) == 0);

}

template <class T>
double TTrapezoid<T>::Square() const {
	TPoint<T> p = this->Center();
	T t1 = 0.5 * fabs((b.x - a.x) * (p.y - a.y) - (p.x - a.x) * (b.y - a.y));
	T t2 = 0.5 * fabs((c.x - b.x) * (p.y - b.y) - (p.x - b.x) * (c.y - b.y));
	T t3 = 0.5 * fabs((d.x - c.x) * (p.y - c.y) - (p.x - c.x) * (d.y - c.y));
	T t4 = 0.5 * fabs((a.x - d.x) * (p.y - d.y) - (p.x - d.x) * (a.y - d.y));
	return t1 + t2 + t3 + t4;
}

template <class T>
TPoint<T> TTrapezoid<T>::Center() const {
	TPoint<T> p;
	T x = (a.x + b.x + c.x + d.x) /4;
	T y = (a.y + b.y + c.y + d.y) /4;
	p.x = x;
	p.y = y;
	
	return p;
}

template <class T>
void TTrapezoid<T>::Print() const {
	std::cout << a << b << c << d << "\n";
}




#endif