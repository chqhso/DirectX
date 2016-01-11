#ifndef D_MATERIAL_H
#define D_MATERIAL_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"
#include "../Material.h"

struct KParsedMaterial;

class DMaterial{
public:
	//D3DMATERIAL9		material;
	Material			material;
//	float				opacity;
	LPDIRECT3DTEXTURE9	pTex[4];
public:
	DMaterial(){
		for (int i = 0; i < 4; i++){
			pTex[i] = NULL;
		}
	}
	DMaterial(LPDIRECT3DDEVICE9 pDev, const KParsedMaterial& mat);
	~DMaterial(){
		for (int i = 0; i < 4; i++){
			REL(pTex[i]);
		}
	}
	void SetMaterial(LPDIRECT3DDEVICE9 pDev, const KParsedMaterial& mat);
};

#endif