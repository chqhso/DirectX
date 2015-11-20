#ifndef DEFINE_H
#define DEFINE_H

#include <list>
#include <map>
#include <string>
#include <vector>
#include <cassert>

#include "Utility\Vector3.h"
#include "Utility\Vector2.h"
#include "Utility\Vector4.h"
#include "Utility\Color4.h"
#include "Utility\Color3.h"
#include "Utility\CodeProjectSingleton.h"
#include "Utility\Matrix4x4.h"
#include "Utility\Quaternion.h"
//#include "Utility\Material.h"
//#include "Parser\KParsedData.h"
//#include "Parser\KParser.h"
#include "Utility\KLog.h"

class KParser;
class KParsedData;
class Material;
class KParsedMesh;

#ifndef MAINBODY
#define DECLARE extern
#else
#define DECLARE
#endif

#define REL(p) { if(p) p->Release(); p = NULL; }
#define DEL(p) { if(p) delete p; p = NULL; }
#define DELS(p) { if(p) delete[] p; }
#define MAX_STR_LEN 128
#define BLENDINDEX(i4, i3, i2, i1) (( i4 ) << 24 | ( i3 ) << 16 | ( i2 ) << 8 | ( i1 ))
#define IS_IN_RANGE(value, r0, r1) (( ((r0) <= (value)) && ((value) <= (r1)) ) ? 1 : 0)

template<typename TContainer>
inline void stl_wipe(TContainer& container){
	for (TContainer::iterator i = container.begin(); i != container.end(); i++)
		delete *i;
	container.clear();
}

template<typename T>
void stl_wipe_vector(std::vector<T>& rVector){
	std::vector<T> emptyData;
	rVector.swap(emptyData);
}

inline int Log2(int n){
	for (int i = 1; i < 64; i++){
		n = n >> 1;
		if (n == 1) return i;
	}
	return 1;
}
inline int Pow2(int n){
	int val = 1;
	val = val << n;
	return val;
}


struct Index3w{
	unsigned short i[3];
};
/// used ParsedMesh, KParser
struct Index3i{
	//int i[3];
	unsigned long i[3];
};
/// used ParsedMesh
struct IndexWidthID{
	int ID;
	Index3i index;
};
/// used ParsedMesh
struct VertWeight{
	std::vector<int> ID;
	std::vector<float> fWeight;
	~VertWeight() { stl_wipe_vector(ID); stl_wipe_vector(fWeight); }
};
/// used ParsedMesh
struct VertMerged{
	Vector3 p;			// pos
	float b[3];			// blend weight
	unsigned int i;		// index
	Vector3 n;			// normal
	Vector2 t;			// texture coord
};
struct KeyRot{
	float frame;
	Quaternion value;
};
struct KeyPos{
	float frame;
	Vector3 value;
};
struct KeyScl{
	float frame;
	Vector3 value;
};
/// used ParsedMesh
struct Track{
	float				start;
	float				end;
	std::vector<KeyPos>	pos;
	std::vector<KeyRot>	rot;
	std::vector<KeyScl>	scl;
	~Track() { stl_wipe_vector(pos); stl_wipe_vector(rot); stl_wipe_vector(scl); }
};
/// used KParsedData
//struct Material{
//	Color3 ambient;
//	Color3 diffuse;
//	Color3 specular;
//	Color3 emissive;
//	float power;
//	float opacity;
//	std::string strMapDiffuse;
//	std::string strMapSpecular;
//	std::string strMapBump;
//	std::string strMapDisplace;
//};
// used KParsedData
struct Info{
	std::string strFilename;
	int nObjectCount;
	int nMeshCount;
	float fAnimationStart;
	float fAnimationEnd;
	int nKeyType;
	int nSkinType;
	std::vector<std::string> strObjectNameTable;
	std::vector<int> BoneTable;
	~Info(){ stl_wipe_vector(strObjectNameTable); stl_wipe_vector(BoneTable); }
};


#endif