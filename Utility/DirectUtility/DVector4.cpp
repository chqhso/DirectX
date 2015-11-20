#include "DVector4.h"

DVector4::DVector4(){
	vector.x = 0.0f;
	vector.y = 0.0f;
	vector.z = 0.0f;
	vector.w = 0.0f;
}
DVector4::DVector4(float x, float y, float z, float w){
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
}
DVector4::DVector4(const Vector3& vec, float w){
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = vec.z;
	vector.w = w;
}
DVector4::DVector4(const Vector4& vec){
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = vec.z;
	vector.w = vec.w;
}
void DVector4::Copy(Vector4& vec){
	vec.x = vector.x;
	vec.y = vector.y;
	vec.z = vector.z;
	vec.w = vector.w;
}