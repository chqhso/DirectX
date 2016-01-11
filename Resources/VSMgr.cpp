#include "VSMgr.h"
#include "../Utility/Matrix4x4.h"
#include "../Utility/Vector2.h"
#include "../Utility/Vector3.h"
#include "../Utility/Vector4.h"
#include "../Utility/Color32.h"

VSMgr::~VSMgr(){
	REL(m_pVSTable->pDecl);
	REL(m_pVSTable->pShader);
	REL(m_pVSTable->pConstantTable);
	DEL(m_pVSTable);
}

bool VSMgr::Load(std::string filename){
	D3DVERTEXELEMENT9			decl[MAX_FVF_DECL_SIZE];

	m_pVSTable = new VSTable();
	m_pVSTable->name = filename;

	// FVF를 사용해서 정점선언값을 자동으로 채워넣는다.
	D3DXDeclaratorFromFVF(CustomVertex::FVF, decl);
	// 정점선언값으로 m_pShaderDecl을 생성한다.
	m_pDev->CreateVertexDeclaration(decl, &m_pVSTable->pDecl);
	LPD3DXBUFFER pCode;

	// 정점쉐이더 파일을 읽어와서 정점쉐이더 인터페이스를 생성한다.
	//if (FAILED(D3DXAssembleShaderFromFile(filename.c_str(), NULL, NULL, 0, &pCode, NULL)))
	//	return false;

	if (FAILED(D3DXCompileShaderFromFile(filename.c_str(), NULL, NULL, "vs_main", "vs_2_0", D3DXSHADER_DEBUG, &pCode, NULL, &m_pVSTable->pConstantTable)))
		return false;

	m_pDev->CreateVertexShader((DWORD*)pCode->GetBufferPointer(), &m_pVSTable->pShader);

	REL(pCode);

	return true;
}
bool VSMgr::SetMatrix(std::string regName, const Matrix4x4& m){
	//if (FAILED(m_pVSTable->pConstantTable->SetMatrix(m_pDev, regName.c_str(), m)))
	//if (FAILED(m_pVSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*&)m, 16)))
	//	return false;
	//return true;
	return SetFloatArray(regName, (float*)&m, 16);
}
bool VSMgr::SetVector4(std::string regName, const Vector4& v){
	//if (FAILED(m_pVSTable->pConstantTable->SetVector(m_pDev, regName.c_str(), v)))
	//if (FAILED(m_pVSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*)&v, 4)))
	//	return false;
	//return true;
	return SetFloatArray(regName, (float*)&v, 4);
}
bool VSMgr::SetVector3(std::string regName, const Vector3& v){
	//if (FAILED(m_pVSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*)&v, 3)))
	//	return false;
	//return true;
	return SetFloatArray(regName, (float*)&v, 3);
}
bool VSMgr::SetVector2(std::string regName, const Vector2& v){
	//if (FAILED(m_pVSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*)&v, 2)))
	//	return false;
	//return true;
	return SetFloatArray(regName, (float*)&v, 2);
}
bool VSMgr::SetColor32(std::string regName, const Color32& col){
	return SetFloatArray(regName, (float*)&col, 4);
}
bool VSMgr::SetFloat(std::string regName, float f){
	if (FAILED(m_pVSTable->pConstantTable->SetFloat(m_pDev, regName.c_str(), f)))
		return false;
	return true;
}
bool VSMgr::SetFloatArray(std::string regName, const float* f, int size){
	if (FAILED(m_pVSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), f, size)))
		return false;
	return true;
}
bool VSMgr::SetTexture(std::string regName, LPDIRECT3DTEXTURE9 pTex){
	D3DXHANDLE handle;
	handle = m_pVSTable->pConstantTable->GetConstantByName(NULL, regName.c_str());
	if (handle){
		D3DXCONSTANT_DESC constDesc;
		UINT count;

		m_pVSTable->pConstantTable->GetConstantDesc(handle, &constDesc, &count);
		m_pDev->SetTexture(constDesc.RegisterIndex, pTex);
		
		return true;
	}
	return false;
}