#include "DTerrain.h"
#include "Dib.h"

DTerrain::DTerrain(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){
	m_cxDIB = 0;
	m_czDIB = 0;
	m_cyDIB = 0;
	m_vfScale = Vector3(1.0f, 1.0f, 1.0f);
	//m_pvHeightMap = nullptr;
	for (int i = 0; i < MAX_TERRAIN_TEX; i++) m_pTex[i] = NULL;
	m_pVB = NULL;
	m_pIB = NULL;
	m_nTriangles = 0;
	m_pQuadTree = NULL;
}
DTerrain::~DTerrain(){
	_Destroy();
}

/**
 * @brief ������ü�� �ʱ�ȭ�Ѵ�.
 * @param pvfScale : ���̸��� x, y, z���� ���� ô����(scale vector)
 * @param fLODRatio : LODó���ÿ� ���� ��
 * @param sHeightMap : ���̸ʿ� BMP���ϸ�
 * @param sTex : ��¿� Texture���ϸ�
 */
bool DTerrain::Create(Vector3 pvfScale, float fLODRatio, std::string sHeightMap, std::string sTex[MAX_TERRAIN_TEX]){
	m_vfScale = pvfScale;
	m_fLODRatio = fLODRatio;
	if (FAILED(_BuildHeightMap(sHeightMap))){
		_Destroy();
		return false;
	}
	if (FAILED(_LoadTextures(sTex))){
		_Destroy();
		return false;
	}
	if (FAILED(_CreateVIB())){
		_Destroy();
		return false;
	}
	m_pQuadTree = new QuadTree(m_cxDIB, m_czDIB);
	if (FAILED(_BuildQuadTree())){
		_Destroy();
		return false;
	}
	return true;
}
float	DTerrain::GetHeight(int x, int z){
	//return GetVertex(x, z)->p.vector.y;
	return GetVertex(x, z)->p.y;
}
/// ȭ�鿡 ������ ����Ѵ�. TODO
HRESULT		DTerrain::_Render(){
	m_pDev->SetTexture(0, m_pTex[0]);
	m_pDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

	m_pDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(CustomVertex));
	m_pDev->SetFVF(CustomVertex::FVF);
	m_pDev->SetIndices(m_pIB);
	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_cxDIB * m_czDIB, 0, m_nTriangles);

	return S_OK;
}
/// ȭ�鿡 ������ ����Ѵ�. TODO : ���� 32��Ʈ�� ���� 16��Ʈ�� ���������ϰ��ϱ�
void	DTerrain::Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){
	LPDWORD pl;

	m_pDev->SetVertexDeclaration(pVSMgr->GetVSTable()->pDecl);
	m_pDev->SetVertexShader(pVSMgr->GetVSTable()->pShader);
	m_pDev->SetPixelShader(pPSMgr->GetPSTable()->pShader);

	pPSMgr->SetTexture("DiffuseSampler", m_pTex[0]);

	m_pIB->Lock(0, (m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(Index3i), (void**)&pl, 0);
	m_nTriangles = m_pQuadTree->GenerateIndex(pl, m_pvHeightMap, *m_pFrustum, m_fLODRatio);
	m_pIB->Unlock();
	//_Render();
	
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(CustomVertex));
	m_pDev->SetIndices(m_pIB);
	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_cxDIB * m_czDIB, 0, m_nTriangles);

	pPSMgr->SetTexture("DiffuseSampler", NULL);

	m_pDev->SetVertexDeclaration(NULL);
	m_pDev->SetVertexShader(NULL);
	m_pDev->SetPixelShader(NULL);
}
/// ������ü�� �޸𸮿��� �Ұ��Ѵ�.
HRESULT		DTerrain::_Destroy(){
	DEL(m_pQuadTree);
	//DELS(m_pvHeightMap);
	stl_wipe_vector(m_pvHeightMap);
	REL(m_pVB);
	REL(m_pIB);
	for (int i = 0; i < MAX_TERRAIN_TEX; i++){
		REL(m_pTex[i]);
	}
	return S_OK;
}
/// ������ü���� ����� �ؽ��ĸ� �о���δ�.
HRESULT		DTerrain::_LoadTextures(std::string Filename[MAX_TERRAIN_TEX]){
	for (int i = 0; i < MAX_TERRAIN_TEX; i++){
		D3DXCreateTextureFromFile(m_pDev, Filename[i].c_str(), &m_pTex[i]);
	}
	return S_OK;
}
/// bmp������ ��� ���̸��� �����Ѵ�.
HRESULT		DTerrain::_BuildHeightMap(std::string Filename){
	//unsigned char *pDIB = DibLoadHandle(Filename.c_str());
	unsigned char *pDIB = DibLoadHandle(const_cast<LPSTR>(Filename.c_str()));
	if (!pDIB) return E_FAIL;

	m_cxDIB = DIB_CX(pDIB);
	m_czDIB = DIB_CY(pDIB);

	// m_cxDIB�� m_czDIB�� (2^n+1)�� �ƴѰ�� E_FAIL�� ��ȯ
	int n = Log2(m_cxDIB);
	if ((Pow2(n) + 1) != m_cxDIB) return E_FAIL;
	n = Log2(m_czDIB);
	if ((Pow2(n) + 1) != m_czDIB) return E_FAIL;

	//m_pvHeightMap = new CustomVertex[m_cxDIB * m_czDIB];
	m_pvHeightMap.resize(m_cxDIB * m_czDIB);

	CustomVertex v;
	for (long z = 0; z < m_czDIB; z++){
		for (long x = 0; x < m_cxDIB; x++){
			//v.p.vector.x = (float)((x - m_cxDIB / 2) * m_vfScale.x);
			//v.p.vector.z = -(float)((z - m_czDIB / 2) * m_vfScale.z);
			//v.p.vector.y = (float)(*(DIB_DATAXY_INV(pDIB, x, z))) * m_vfScale.y;
			v.p.x = (float)((x - m_cxDIB / 2) * m_vfScale.x);
			v.p.z = -(float)((z - m_czDIB / 2) * m_vfScale.z);
			v.p.y = (float)(*(DIB_DATAXY_INV(pDIB, x, z))) * m_vfScale.y;
//			D3DXVec3Normalize(&v.n.vector, &v.p.vector);
			v.n = Normalized(v.p);
//			v.t.vector.x = (float)x / (float)(m_cxDIB - 1);
//			v.t.vector.y = (float)z / (float)(m_czDIB - 1);
			v.t.x = (float)x / (float)(m_cxDIB - 1);
			v.t.y = (float)z / (float)(m_czDIB - 1);
			m_pvHeightMap[x + z * m_czDIB] = v;
		}
	}

	DibDeleteHandle(pDIB);
	return S_OK;
}
/// bmp������ ũ�⿡ ���缭 ����Ʈ���� �����Ѵ�.
HRESULT		DTerrain::_BuildQuadTree(){
	m_pQuadTree->Build(m_pvHeightMap);
	return S_OK;
}
/// ����, �ε��� ���۸� �����Ѵ�. TODO : ���� 32��Ʈ�� ���� 16��Ʈ�� ���������ϰ��ϱ�
HRESULT		DTerrain::_CreateVIB(){
	// VB����
	if (FAILED(m_pDev->CreateVertexBuffer(m_cxDIB * m_czDIB * sizeof(CustomVertex), 0, CustomVertex::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL))){
		_Destroy();
		return E_FAIL;
	}
	VOID* pVertices;
	//TerrainVertex* pVertices;
	if (FAILED(m_pVB->Lock(0, m_cxDIB * m_czDIB * sizeof(CustomVertex), (void**)&pVertices, 0))){
		_Destroy();
		return E_FAIL;
	}
	memcpy(pVertices, &m_pvHeightMap[0], m_cxDIB * m_czDIB * sizeof(CustomVertex));
	m_pVB->Unlock();

	// IB���� 32bit
	if (FAILED(m_pDev->CreateIndexBuffer((m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(Index3i), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIB, NULL))){
		_Destroy();
		return E_FAIL;
	}

	return S_OK;
}
/// x,z��ġ�� �������� ����.
CustomVertex* DTerrain::GetVertex(int x, int z){
	return &m_pvHeightMap[x + z * m_cxDIB];
	//return (m_pvHeightMap + x + z * m_cxDIB);
}
void DTerrain::testCreateIB(){
	Index3i i;
	Index3i* pI;

	if (FAILED(m_pIB->Lock(0, (m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(Index3i), (void**)&pI, 0))){
		_Destroy();
	}

	for (unsigned long z = 0; z < m_czDIB - 1; z++){
		for (DWORD x = 0; x < m_cxDIB - 1; x++){
			i.i[0] = (z * m_cxDIB + x);
			i.i[1] = (z * m_cxDIB + x + 1);
			i.i[2] = ((z + 1) * m_cxDIB + x);
			*pI++ = i;
			i.i[0] = ((z + 1) * m_cxDIB + x);
			i.i[1] = (z * m_cxDIB + x + 1);
			i.i[2] = ((z + 1) * m_cxDIB + x + 1);
			*pI++ = i;
		}
	}

	m_nTriangles = (m_cxDIB - 1) * (m_czDIB - 1) * 2;

	m_pIB->Unlock();
}