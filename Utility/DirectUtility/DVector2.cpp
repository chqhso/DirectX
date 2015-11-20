#include "DVector2.h"
DVector2::DVector2(){
	vector.x = 0.0f;
	vector.y = 0.0f;
}
DVector2::DVector2(float x, float y){
	vector.x = x;
	vector.y = y;
}
DVector2::DVector2(const Vector2& vec){
	vector.x = vec.x;
	vector.y = vec.y;
}
DVector2::DVector2(const Vector3& vec){
	vector.x = vec.x;
	vector.y = vec.y;
}
DVector2::DVector2(const Vector4& vec){
	vector.x = vec.x;
	vector.y = vec.y;
}
void DVector2::Copy(Vector2& vec){
	vec.x = vector.x;
	vec.y = vector.y;
}