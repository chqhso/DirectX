#ifndef RECT_H
#define RECT_H

class Vector2;

class Rect{
public:
	long left;
	long top;
	long right;
	long bottom;
public:
	Rect();
	Rect(long _left, long _top, long _right, long _bottom);
	void SetRect(long _left, long _top, long _right, long _bottom);
	bool IsInRect(const Vector2& vec);
};

#endif