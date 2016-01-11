#ifndef D_TERRAIN_H
#define D_TERRAIN_H

#include "../../DirectDefine.h"
#include "../../Interface/ITerrain.h"

class DTerrain : public ITerrain{
public:
	LPDIRECT3DDEVICE9 m_pDev;
	LPDIRECT3DTEXTURE9 m_pTex[MAX_TERRAIN_TEX];
	//CustomVertex* m_pvHeightMap;
	std::vector<CustomVertex> m_pvHeightMap;
	//std::vector<TerrainVertex> m_pvHeightMap;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
public:
	DTerrain(LPDIRECT3DDEVICE9 pDev);
	~DTerrain();
	virtual bool Create(Vector3 pvfScale, float fLODRatio, std::string sHeightMap, std::string sTex[MAX_TERRAIN_TEX]) override;
	virtual float	GetHeight(int x, int z) override;
	virtual void	Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) override;
private:
	/// ������ü�� �޸𸮿��� �Ұ��Ѵ�.
	HRESULT		_Destroy();
	/// ������ü���� ����� �ؽ��ĸ� �о���δ�.
	HRESULT		_LoadTextures(std::string Filename[MAX_TERRAIN_TEX]);
	/// bmp������ ��� ���̸��� �����Ѵ�.
	HRESULT		_BuildHeightMap(std::string Filename);
	/// bmp������ ũ�⿡ ���缭 ����Ʈ���� �����Ѵ�.
	HRESULT		_BuildQuadTree();
	/// ����, �ε��� ���۸� �����Ѵ�. TODO : ���� 32��Ʈ�� ���� 16��Ʈ�� ���������ϰ��ϱ�
	HRESULT		_CreateVIB();
	/// ȭ�鿡 ������ ����Ѵ�.
	HRESULT		_Render();
	/// x,z��ġ�� �������� ����.
	CustomVertex* GetVertex(int x, int z);


	void testCreateIB();
};

#endif