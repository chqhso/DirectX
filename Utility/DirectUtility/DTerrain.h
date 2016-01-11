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
	/// 지형객체를 메모리에서 소거한다.
	HRESULT		_Destroy();
	/// 지형객체에서 사용할 텍스쳐를 읽어들인다.
	HRESULT		_LoadTextures(std::string Filename[MAX_TERRAIN_TEX]);
	/// bmp파일을 열어서 높이맵을 생성한다.
	HRESULT		_BuildHeightMap(std::string Filename);
	/// bmp파일의 크기에 맞춰서 쿼드트리를 생성한다.
	HRESULT		_BuildQuadTree();
	/// 정점, 인덱스 버퍼를 생성한다. TODO : 현재 32비트만 지원 16비트도 대응가능하게하기
	HRESULT		_CreateVIB();
	/// 화면에 지형을 출력한다.
	HRESULT		_Render();
	/// x,z위치의 정점값을 얻어낸다.
	CustomVertex* GetVertex(int x, int z);


	void testCreateIB();
};

#endif