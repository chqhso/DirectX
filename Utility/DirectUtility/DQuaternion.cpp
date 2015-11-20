#include "DQuaternion.h"
DQuaternion::DQuaternion(){
	quaternion.x = 0.0f;
	quaternion.y = 0.0f;
	quaternion.z = 0.0f;
	quaternion.w = 0.0f;
}
DQuaternion::DQuaternion(float x, float y, float z, float w){
	quaternion.x = x;
	quaternion.y = y;
	quaternion.z = z;
	quaternion.w = w;
}
DQuaternion::DQuaternion(const Quaternion& quat){
	quaternion.x = quat.x;
	quaternion.y = quat.y;
	quaternion.z = quat.z;
	quaternion.w = quat.w;
}
void DQuaternion::Copy(Quaternion& quat){
	quat.x = quaternion.x;
	quat.y = quaternion.y;
	quat.z = quaternion.z;
	quat.w = quaternion.w;
}