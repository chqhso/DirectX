#include "Frustum.h"

Frustum::Frustum(){

}
Frustum::~Frustum(){

}
void Frustum::Make(float* matView, float* matProj){
	Matrix4x4 view;
	Matrix4x4 proj;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			view.m[i][j] = matView[i * 4 + j];
			proj.m[i][j] = matProj[i * 4 + j];
		}
	}

	Make(&view, &proj);
}

// 카메라(view) * 프로젝션(projection)행렬을 입력받아 6개의 평면을 만든다.
void Frustum::Make(Matrix4x4* matView, Matrix4x4* matProj){
	Matrix4x4 matInv;

	// 투영행렬까지 거치면 모든 3차원 월드좌표의 점은 (-1, -1, 0) ~ (1, 1, 1)사이의 값으로 바뀐다.
	// m_vtx에 이 동차공간의 경계값을 넣어둔다.
	m_vtx[0].x = -1.0f; m_vtx[0].y = -1.0f; m_vtx[0].z = 0.0f;
	m_vtx[1].x =  1.0f; m_vtx[1].y = -1.0f; m_vtx[1].z = 0.0f;
	m_vtx[2].x =  1.0f; m_vtx[2].y = -1.0f; m_vtx[2].z = 1.0f;
	m_vtx[3].x = -1.0f; m_vtx[3].y = -1.0f; m_vtx[3].z = 1.0f;
	m_vtx[4].x = -1.0f; m_vtx[4].y =  1.0f; m_vtx[4].z = 0.0f;
	m_vtx[5].x =  1.0f; m_vtx[5].y =  1.0f; m_vtx[5].z = 0.0f;
	m_vtx[6].x =  1.0f; m_vtx[6].y =  1.0f; m_vtx[6].z = 1.0f;
	m_vtx[7].x = -1.0f; m_vtx[7].y =  1.0f; m_vtx[7].z = 1.0f;

	// view * proj의 역행렬을 구한다.
	matInv = Matrix4x4::Inverse(*matView * *matProj);

	// Vertex_Desc = Vertex_local * Matrix_world * Matrix_view * Matrix_Proj 인데,
	// Vertex_world = Vertex_local * Matrix_world 이므로,
	// Vertex_Desc = Vertex_world * Matrix_view * Matrix_Proj 이다.
	// Vertex_Desc = Vertex_world * (Matrix_view * Matrix_Proj) 에서
	// Vertex_Desc * Inv(Matrix_view * Matrix_Proj) = Vertex_world가 된다.
	// 그러므로, m_vtx * matInv = Vertex_world가 되어, 월드좌표계의 프러스텀 좌표를 얻을수 있다.
	for (int i = 0; i < 8; i++){
		m_vtx[i] = Matrix4x4::TransformCoord(m_vtx[i], matInv);
	}
	//0번과 5번은 프러스텀중 near평면의 좌측상단과 우측하단이므로, 둘의 좌표를 더해서 2로 나누면
	// 카메라의 좌표를 얻을 수 있다.(정확히 일치하는 것은 아니다)
	m_vPos = (m_vtx[0] + m_vtx[5]) / 2.0f;

	// 얻어진 월드좌표로 프러스텀 평면을 만든다.
	// 벡터가 프러스텀 안쪽에서 받깥쪼그올 나가는 평면들이다.
//	m_plane[0] = Plane(m_vtx[4], m_vtx[7], m_vtx[6]);		// 상 평면(top)
//	m_plane[1] = Plane(m_vtx[0], m_vtx[1], m_vtx[2]);		// 하 평면(bottom)
//	m_plane[2] = Plane(m_vtx[0], m_vtx[4], m_vtx[5]);		// 근 평면(near)
	m_plane[3] = Plane(m_vtx[2], m_vtx[6], m_vtx[7]);		// 원 평면(far)
	m_plane[4] = Plane(m_vtx[0], m_vtx[3], m_vtx[7]);		// 좌 평면(left)
	m_plane[5] = Plane(m_vtx[1], m_vtx[5], m_vtx[6]);		// 우 평면(right)
}

// TODO : 다른함수로 테스트
bool Frustum::IsIn(Vector3* pv){
	if (m_plane[3].DotCoord(*pv) > PLANE_EPSILON) return false;
	if (m_plane[4].DotCoord(*pv) > PLANE_EPSILON) return false;
	if (m_plane[5].DotCoord(*pv) > PLANE_EPSILON) return false;

	return true;
}
bool Frustum::IsInSphere(Vector3* pv, float radius){
	if (m_plane[3].DotCoord(*pv) > (radius + PLANE_EPSILON)) return false;
	if (m_plane[4].DotCoord(*pv) > (radius + PLANE_EPSILON)) return false;
	if (m_plane[5].DotCoord(*pv) > (radius + PLANE_EPSILON)) return false;

	return true;
}