#pragma once
#include "District.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include <iostream>
enum class DistrictType { UNIFIED, DIVIDED };
class DistrictLoader
{
public:
	static bool save(ostream& out, const District& dst);
	static District* load(istream& in);
};

