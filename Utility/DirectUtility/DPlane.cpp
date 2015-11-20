#include "DPlane.h"

DPlane::DPlane(){
	m_Plane.a = 0.0f;
	m_Plane.b = 0.0f;
	m_Plane.c = 0.0f;
	m_Plane.d = 0.0f;
}
DPlane::DPlane(float a, float b, float c, float d){
	m_Plane.a = a;
	m_Plane.b = b;
	m_Plane.c = c;
	m_Plane.d = d;
}
DPlane::DPlane(const Plane& plane){
	m_Plane.a = plane.a;
	m_Plane.b = plane.b;
	m_Plane.c = plane.c;
	m_Plane.d = plane.d;
}
void DPlane::Copy(Plane* plane){
	plane->a = m_Plane.a;
	plane->b = m_Plane.b;
	plane->c = m_Plane.c;
	plane->d = m_Plane.d;
}