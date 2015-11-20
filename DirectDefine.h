#ifndef DIRECT_DEFINE_H
#define DIRECT_DEFINE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

#include "Utility\DirectUtility\DVector2.h"
#include "Utility\DirectUtility\DVector3.h"
#include "Utility\DirectUtility\DVector4.h"
#include "Utility\DirectUtility\DQuaternion.h"

//class DVector2;
//class DVector3;
//class DVector4;
class DColor4;
class DMaterial;
class DMatrix;
class DPlane;

struct ObjectInfo{
	int							nObjectCount;
	int							nMeshCount;
	float						fAnimationStart;
	float						fAnimationEnd;
	int							nKeyType;
	int							nSkinType;
	std::vector<std::string>	strObjectNameTable;
	std::vector<int>			BoneTable;
	std::vector<int>			MeshTable;
	ObjectInfo(){
		stl_wipe_vector(strObjectNameTable);
		stl_wipe_vector(BoneTable);
		stl_wipe_vector(MeshTable);
	}
};

struct CustomVertex{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX3 |
	D3DFVF_TEXCOORDSIZE2(0) |						// texture
	D3DFVF_TEXCOORDSIZE4(1) |						// blend weight
	D3DFVF_TEXCOORDSIZE4(2))						// blend index
	};

	DVector3 p;			// position
	DVector3 n;			// normal
	DVector2 t;			// texture coord
	DVector4 b;			// blend wiehgt
	DVector4 i;			// blend index
};

struct TerrainVertex{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	DVector3 p;
	DVector3 n;
	DVector2 t;
};

struct BoxVertex{
	enum{FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};

	float x, y, z;
	DWORD color;
	BoxVertex(){ x = 0.0f; y = 0.0f; z = 0.0f; color = 0.0f; }
	BoxVertex(float f1, float f2, float f3, DWORD c){ x = f1; y = f2; z = f3; color = c; }
};

struct DBaseKey{
	int			frame;
};
struct DKeyPos : public DBaseKey{
	DVector3	value;
};
struct DKeyRot : public DBaseKey{
	DQuaternion	value;
};
struct DKeyScl : public DBaseKey{
	DVector3	value;
};
struct DKeys{
	std::vector<DKeyPos>	pos;
	std::vector<DKeyRot>	rot;
	std::vector<DKeyScl>	scl;
	~DKeys(){
		stl_wipe_vector(pos);
		stl_wipe_vector(rot);
		stl_wipe_vector(scl);
	}
};

#endif