#ifndef K_PARSED_DATA_H
#define K_PARSED_DATA_H

#include "../Define.h"
#include "KParsedMesh.h"
#include "../Utility/Material.h"

/// XML파일을 파싱한 결과 클래스
class KParsedData{
public:
public:
	Info					m_info;
	std::vector<Material>	m_materialTable;
	std::list<KParsedMesh*>	m_meshList;
public:
	KParsedData(){}
	~KParsedData(){
		stl_wipe_vector(m_materialTable);
		stl_wipe(m_meshList);
	}
};

#endif