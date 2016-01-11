#ifndef K_PARSED_DATA_H
#define K_PARSED_DATA_H

#include "../Define.h"
#include "KParsedMesh.h"
#include "../Utility/Color32.h"

struct KParsedMaterial{
public:
	Color32 ambient;
	Color32 diffuse;
	Color32 specular;
	Color32 emissive;
	float power;
	float opacity;
	std::string strMapDiffuse;
	std::string strMapSpecular;
	std::string strMapBump;
	std::string strMapDisplace;
};

/// XML파일을 파싱한 결과 클래스
struct KParsedData{
public:
public:
	Info					m_info;
	std::vector<KParsedMaterial>	m_materialTable;
	std::list<KParsedMesh*>	m_meshList;
public:
	KParsedData(){}
	~KParsedData(){
		stl_wipe_vector(m_materialTable);
		stl_wipe(m_meshList);
	}
};

#endif