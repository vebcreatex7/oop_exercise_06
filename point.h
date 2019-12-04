#ifndef POINT_H
#define POINT_H 1

#include <iostream>
#include <algorithm>
#include <cmath>


template<class T>
struct TPoint {
	TPoint() {}
	TPoint(T a, T b) : x(a), y(b){}
	T x;
	T y;
	

};

template<class T>
std::ostream& operator << (std::ostream& os, const TPoint<T>& p)
{
	os << p.x << " " << p.y << " ";
	return os;
}

template <class T>
std::istream& operator >> (std::istream& is, TPoint<T>& p)
{
	is >> p.x >> p.y;
	return is;
}

template <class T>
TPoint<T> operator /= ( TPoint<T>& p, int val)
{
	p.x = p.x / val;
	p.y = p.y / val;
	return p;
}

template <class T>
TPoint<T> operator + (const TPoint<T>& p1, const TPoint<T>& p2)
{
	TPoint<T> p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

template <class T>
TPoint<T> operator - (const TPoint<T> p1, const TPoint<T> p2)
{
	TPoint<T> p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

#endif 
