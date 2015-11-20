#include "PSMgr.h"
#include "../Utility/DirectUtility/DMatrix.h"
#include "../Utility/DirectUtility/DVector4.h"
#include "../Utility/DirectUtility/DVector3.h"
#include "../Utility/DirectUtility/DVector2.h"

PSMgr::~PSMgr(){
	REL(m_pPSTable->pDecl);
	REL(m_pPSTable->pShader);
	REL(m_pPSTable->pConstantTable);
	DEL(m_pPSTable);
}

bool PSMgr::Load(std::string filename){
	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE];

	m_pPSTable = new PSTable();
	m_pPSTable->name = filename;

	// FVF를 사용해서 정점선언값을 자동으로 채워넣는다.
	D3DXDeclaratorFromFVF(CustomVertex::FVF, decl);
	// 정점선언값으로 m_pShaderDecl를 생성한다.
	m_pDev->CreateVertexDeclaration(decl, &m_pPSTable->pDecl);
	LPD3DXBUFFER pCode;

	// 정점쉐이더 파일을 읽어와서 정점쉐이더 인터페이스를 생성한다.
	//if (FAILED(D3DXAssembleShaderFromFile((filename.c_str()), NULL, NULL, 0, &pCode, NULL)))
	//	return false;

	if (FAILED(D3DXCompileShaderFromFile(filename.c_str(), NULL, NULL, "ps_main", "ps_2_0", D3DXSHADER_DEBUG, &pCode, NULL, &m_pPSTable->pConstantTable)))
		return false;

	m_pDev->CreatePixelShader((DWORD*)pCode->GetBufferPointer(), &m_pPSTable->pShader);

	REL(pCode);

	return true;
}
bool PSMgr::SetMatrix(std::string regName, DMatrix* m){
	if (FAILED(m_pPSTable->pConstantTable->SetMatrix(m_pDev, regName.c_str(), &m->matrix)))
		return false;
	return true;
}
bool PSMgr::SetVector4(std::string regName, DVector4* v){
	if (FAILED(m_pPSTable->pConstantTable->SetVector(m_pDev, regName.c_str(), &v->vector)))
		return false;
	return true;
}
bool PSMgr::SetVector3(std::string regName, DVector3* v){
	if (FAILED(m_pPSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*)&v->vector, 3)))
		return false;
	return true;
}
bool PSMgr::SetVector2(std::string regName, DVector2* v){
	if (FAILED(m_pPSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), (float*)&v->vector, 2)))
		return false;
	return true;

}
bool PSMgr::SetFloat(std::string regName, float f){
	if (FAILED(m_pPSTable->pConstantTable->SetFloat(m_pDev, regName.c_str(), f)))
		return false;
	return true;
}
bool PSMgr::SetTexture(std::string regName, LPDIRECT3DTEXTURE9 pTex){
	D3DXHANDLE handle;
	handle = m_pPSTable->pConstantTable->GetConstantByName(NULL, regName.c_str());
	if (handle){
		D3DXCONSTANT_DESC constDesc;
		UINT count;

		m_pPSTable->pConstantTable->GetConstantDesc(handle, &constDesc, &count);
		m_pDev->SetTexture(constDesc.RegisterIndex, pTex);

		return true;
	}
	return false;
}
bool PSMgr::SetMatrix(std::string regName, float* f){
	DMatrix mat;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			mat.matrix.m[i][j] = f[i * 4 + j];
		}
	}
	if (FAILED(m_pPSTable->pConstantTable->SetMatrix(m_pDev, regName.c_str(), &mat.matrix)))
		return false;
	return true;
}
bool PSMgr::SetVector4(std::string regName, float* f){
	DVector4 vec;
	vec.vector.x = f[0];
	vec.vector.y = f[1];
	vec.vector.z = f[2];
	vec.vector.w = f[3];
	if (FAILED(m_pPSTable->pConstantTable->SetVector(m_pDev, regName.c_str(), &vec.vector)))
		return false;
	return true;
}
bool PSMgr::SetVector3(std::string regName, float* f){
	if (FAILED(m_pPSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), f, 3)))
		return false;
	return true;
}
bool PSMgr::SetVector2(std::string regName, float* f){
	if (FAILED(m_pPSTable->pConstantTable->SetFloatArray(m_pDev, regName.c_str(), f, 2)))
		return false;
	return true;
}