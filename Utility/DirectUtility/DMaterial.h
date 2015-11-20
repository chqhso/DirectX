#ifndef D_MATERIAL_H
#define D_MATERIAL_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DMaterial{
public:
	D3DMATERIAL9		material;
	float				opacity;
	LPDIRECT3DTEXTURE9	pTex[4];
public:
	DMaterial(){
		for (int i = 0; i < 4; i++){
			pTex[i] = NULL;
		}
	}
	DMaterial(LPDIRECT3DDEVICE9 pDev, const Material& mat);
	~DMaterial(){
		for (int i = 0; i < 4; i++){
			REL(pTex[i]);
		}
	}
	void SetMaterial(LPDIRECT3DDEVICE9 pDev, const Material& mat);
};

#endif