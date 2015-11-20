#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Define.h"

class Material{
public:
	Color3 ambient;
	Color3 diffuse;
	Color3 specular;
	Color3 emissive;
	float power;
	float opacity;
	std::string strMapDiffuse;
	std::string strMapSpecular;
	std::string strMapBump;
	std::string strMapDisplace;
};

#endif