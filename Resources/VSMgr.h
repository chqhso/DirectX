#ifndef VS_MGR_H
#define VS_MGR_H

#include "../DirectDefine.h"
#include "../Define.h"

struct Matrix4x4;
struct Vector4;
struct Vector3;
struct Vector2;
struct Color32;

struct VSTable{
	std::string							name;
	LPDIRECT3DVERTEXDECLARATION9		pDecl;
	LPDIRECT3DVERTEXSHADER9				pShader;
	LPD3DXCONSTANTTABLE					pConstantTable;
};

class VSMgr{
	LPDIRECT3DDEVICE9			m_pDev;
	VSTable*					m_pVSTable;
public:
	VSMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){}
	~VSMgr();

	bool Load(std::string filename);
	VSTable* GetVSTable(){ return m_pVSTable; }

	bool SetMatrix(std::string regName, const Matrix4x4& m);
	bool SetVector4(std::string regName, const Vector4& v);
	bool SetVector3(std::string regName, const Vector3& v);
	bool SetVector2(std::string regName, const Vector2& v);
	bool SetColor32(std::string regName, const Color32& col);
	bool SetFloat(std::string regName, float f);
	bool SetFloatArray(std::string regName, const float* f, int size);
	bool SetTexture(std::string regName, LPDIRECT3DTEXTURE9 pTex);
};

#endif