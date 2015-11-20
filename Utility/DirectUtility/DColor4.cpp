#include "DColor4.h"
DColor4::DColor4(){
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;
	color.a = 0.0f;
}
DColor4::DColor4(float r, float g, float b, float a){
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}
DColor4::DColor4(const Color3& col){
	color.r = col.r;
	color.g = col.g;
	color.b = col.b;
	color.a = 1.0f;
}
DColor4::DColor4(const Color3& col, float a){
	color.r = col.r;
	color.g = col.g;
	color.b = col.b;
	color.a = a;
}
DColor4::DColor4(const Color4& col){
	color.r = col.r;
	color.g = col.g;
	color.b = col.b;
	color.a = col.a;
}
void DColor4::Copy(Color4& col){
	col.r = color.r;
	col.g = color.g;
	col.b = color.b;
	col.a = color.a;
}