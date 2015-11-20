#include "Rect.h"
#include "Vector2.h"

Rect::Rect() : left(0), top(0), right(0), bottom(0){}
Rect::Rect(long _left, long _top, long _right, long _bottom){
	SetRect(_left, _top, _right, _bottom);
}
void Rect::SetRect(long _left, long _top, long _right, long _bottom){
	left = _left;
	top = _top;
	right = _right;
	bottom = _bottom;
}
bool Rect::IsInRect(const Vector2& vec){
	if ((left <= vec.x) && (vec.x <= right) &&
		(bottom <= vec.y) && (vec.y <= top))
		return true;
	return false;
}