#include "DMaterial.h"
#include "../../Parser/KParsedData.h"
//#include "DColor4.h"

DMaterial::DMaterial(LPDIRECT3DDEVICE9 pDev, const KParsedMaterial& mat){
	SetMaterial(pDev, mat);
}
void DMaterial::SetMaterial(LPDIRECT3DDEVICE9 pDev, const KParsedMaterial& mat){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	std::string str;

	//opacity = mat.opacity;
	material.opacity = mat.opacity;

	// Ȯ�걤
//	DColor4 diffuse(mat.diffuse.r, mat.diffuse.g, mat.diffuse.b, opacity);
//	material.Diffuse = diffuse.color;
	material.diffuse = Color32(mat.diffuse.r, mat.diffuse.g, mat.diffuse.b);

	// ȯ�汤
//	DColor4 ambient(mat.ambient.r, mat.ambient.g, mat.ambient.b, opacity);
//	material.Ambient = ambient.color;
	material.ambient = Color32(mat.ambient.r, mat.ambient.g, mat.ambient.b);

	// �ݻ籤
//	DColor4 specular(mat.specular.r, mat.specular.g, mat.specular.b, opacity);
//	material.Specular = specular.color;
	material.specular = Color32(mat.specular.r, mat.specular.g, mat.specular.b);

	// �߻걤
//	DColor4 emissive(mat.emissive.r, mat.emissive.g, mat.emissive.b, opacity);
//	material.Emissive = emissive.color;
	material.emissive = Color32(mat.emissive.r, mat.emissive.g, mat.emissive.b);

	// �������
	material.power = mat.power;

	// Ȯ��� �ؽ���
	pTex[0] = NULL;
	char* s = (char*)mat.strMapDiffuse.c_str();
	_splitpath_s(mat.strMapDiffuse.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[0]);

	// ������ �ؽ���
	pTex[1] = NULL;
	_splitpath_s(mat.strMapBump.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[1]);

	// �ݻ�� �ؽ���
	pTex[2] = NULL;
	_splitpath_s(mat.strMapSpecular.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[2]);

	// �׿��� �߰����� �ؽ���
	pTex[3] = NULL;
	_splitpath_s(mat.strMapDisplace.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[3]);
}