#ifndef DIRECT_DEFINE_H
#define DIRECT_DEFINE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

#include "Define.h"
#include "Utility\Vector2.h"
#include "Utility\Vector3.h"
#include "Utility\Vector4.h"
#include "Utility\Color32.h"

class DMaterial;
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

	Vector3 p;			// position
	Vector3 n;			// normal
	Vector2 t;			// texture coord
	Vector4 b;			// blend wiehgt
	Vector4 i;			// blend index
};

//struct TerrainVertex{
//	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
//	DVector3 p;
//	DVector3 n;
//	DVector2 t;
//};

//struct BoxVertex{
//	enum{FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
//
//	float x, y, z;
//	DWORD color;
//	BoxVertex(){ x = 0.0f; y = 0.0f; z = 0.0f; color = 0.0f; }
//	BoxVertex(float f1, float f2, float f3, DWORD c){ x = f1; y = f2; z = f3; color = c; }
//};

struct DBaseKey{
	float			frame;
};
struct DKeyPos : public DBaseKey{
	Vector3	value;
};
struct DKeyRot : public DBaseKey{
	Quaternion	value;
};
struct DKeyScl : public DBaseKey{
	Vector3	value;
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