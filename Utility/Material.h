#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color32.h"

struct Material{
public:
	Color32 ambient;
	Color32 diffuse;
	Color32 specular;
	Color32 emissive;
	float power;
	float opacity;
};

#endif