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

// ī�޶�(view) * ��������(projection)����� �Է¹޾� 6���� ����� �����.
void Frustum::Make(Matrix4x4* matView, Matrix4x4* matProj){
	Matrix4x4 matInv;

	// ������ı��� ��ġ�� ��� 3���� ������ǥ�� ���� (-1, -1, 0) ~ (1, 1, 1)������ ������ �ٲ��.
	// m_vtx�� �� ���������� ��谪�� �־�д�.
	m_vtx[0].x = -1.0f; m_vtx[0].y = -1.0f; m_vtx[0].z = 0.0f;
	m_vtx[1].x =  1.0f; m_vtx[1].y = -1.0f; m_vtx[1].z = 0.0f;
	m_vtx[2].x =  1.0f; m_vtx[2].y = -1.0f; m_vtx[2].z = 1.0f;
	m_vtx[3].x = -1.0f; m_vtx[3].y = -1.0f; m_vtx[3].z = 1.0f;
	m_vtx[4].x = -1.0f; m_vtx[4].y =  1.0f; m_vtx[4].z = 0.0f;
	m_vtx[5].x =  1.0f; m_vtx[5].y =  1.0f; m_vtx[5].z = 0.0f;
	m_vtx[6].x =  1.0f; m_vtx[6].y =  1.0f; m_vtx[6].z = 1.0f;
	m_vtx[7].x = -1.0f; m_vtx[7].y =  1.0f; m_vtx[7].z = 1.0f;

	// view * proj�� ������� ���Ѵ�.
	matInv = Matrix4x4::Inverse(*matView * *matProj);

	// Vertex_Desc = Vertex_local * Matrix_world * Matrix_view * Matrix_Proj �ε�,
	// Vertex_world = Vertex_local * Matrix_world �̹Ƿ�,
	// Vertex_Desc = Vertex_world * Matrix_view * Matrix_Proj �̴�.
	// Vertex_Desc = Vertex_world * (Matrix_view * Matrix_Proj) ����
	// Vertex_Desc * Inv(Matrix_view * Matrix_Proj) = Vertex_world�� �ȴ�.
	// �׷��Ƿ�, m_vtx * matInv = Vertex_world�� �Ǿ�, ������ǥ���� �������� ��ǥ�� ������ �ִ�.
	for (int i = 0; i < 8; i++){
		m_vtx[i] = Matrix4x4::TransformCoord(m_vtx[i], matInv);
	}
	//0���� 5���� ���������� near����� ������ܰ� �����ϴ��̹Ƿ�, ���� ��ǥ�� ���ؼ� 2�� ������
	// ī�޶��� ��ǥ�� ���� �� �ִ�.(��Ȯ�� ��ġ�ϴ� ���� �ƴϴ�)
	m_vPos = (m_vtx[0] + m_vtx[5]) / 2.0f;

	// ����� ������ǥ�� �������� ����� �����.
	// ���Ͱ� �������� ���ʿ��� �ޱ��ɱ׿� ������ �����̴�.
//	m_plane[0] = Plane(m_vtx[4], m_vtx[7], m_vtx[6]);		// �� ���(top)
//	m_plane[1] = Plane(m_vtx[0], m_vtx[1], m_vtx[2]);		// �� ���(bottom)
//	m_plane[2] = Plane(m_vtx[0], m_vtx[4], m_vtx[5]);		// �� ���(near)
	m_plane[3] = Plane(m_vtx[2], m_vtx[6], m_vtx[7]);		// �� ���(far)
	m_plane[4] = Plane(m_vtx[0], m_vtx[3], m_vtx[7]);		// �� ���(left)
	m_plane[5] = Plane(m_vtx[1], m_vtx[5], m_vtx[6]);		// �� ���(right)
}

// TODO : �ٸ��Լ��� �׽�Ʈ
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