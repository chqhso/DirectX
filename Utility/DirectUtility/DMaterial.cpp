#include "DMaterial.h"
#include "../Material.h"
#include "DColor4.h"

DMaterial::DMaterial(LPDIRECT3DDEVICE9 pDev, const Material& mat){
	SetMaterial(pDev, mat);
}
void DMaterial::SetMaterial(LPDIRECT3DDEVICE9 pDev, const Material& mat){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	std::string str;

	opacity = mat.opacity;

	// 확산광
	DColor4 diffuse(mat.diffuse.r, mat.diffuse.g, mat.diffuse.b, opacity);
	material.Diffuse = diffuse.color;

	// 환경광
	DColor4 ambient(mat.ambient.r, mat.ambient.g, mat.ambient.b, opacity);
	material.Ambient = ambient.color;

	// 반사광
	DColor4 specular(mat.specular.r, mat.specular.g, mat.specular.b, opacity);
	material.Specular = specular.color;

	// 발산광
	DColor4 emissive(mat.emissive.r, mat.emissive.g, mat.emissive.b, opacity);
	material.Emissive = emissive.color;

	// 제곱계수
	material.Power = mat.power;

	// 확산맵 텍스쳐
	pTex[0] = NULL;
	char* s = (char*)mat.strMapDiffuse.c_str();
	_splitpath_s(mat.strMapDiffuse.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[0]);

	// 법선맵 텍스쳐
	pTex[1] = NULL;
	_splitpath_s(mat.strMapBump.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[1]);

	// 반사맵 텍스쳐
	pTex[2] = NULL;
	_splitpath_s(mat.strMapSpecular.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[2]);

	// 그외의 추가적인 텍스쳐
	pTex[3] = NULL;
	_splitpath_s(mat.strMapDisplace.c_str(), drive, dir, fname, ext);
	str = fname; str += ext;
	D3DXCreateTextureFromFile(pDev, str.c_str(), &pTex[3]);
}