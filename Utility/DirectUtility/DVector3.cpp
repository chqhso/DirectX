#include "DVector3.h"
DVector3::DVector3(){
	vector.x = 0.0f;
	vector.y = 0.0f;
	vector.z = 0.0f;
}
DVector3::DVector3(float x, float y, float z){
	vector.x = x;
	vector.y = y;
	vector.z = z;
}
DVector3::DVector3(const Vector2& vec, float z){
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = z;
}
DVector3::DVector3(const Vector3& vec){
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = vec.z;
}
DVector3::DVector3(const Vector4& vec){
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = vec.z;
}
void DVector3::Copy(Vector3& vec){
	vec.x = vector.x;
	vec.y = vector.y;
	vec.z = vector.z;
}