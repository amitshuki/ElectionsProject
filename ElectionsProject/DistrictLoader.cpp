#include "DistrictLoader.h"

using namespace std;
bool DistrictLoader::save(ostream& out,const District& dst) {
	DistrictType type;
	if (typeid(dst) == typeid(DividedDistrict))
		type = DistrictType::DIVIDED;
	else if(typeid(dst)==typeid(UnifiedDistrict))
		type = DistrictType::UNIFIED;

	out.write(rcastcc(&type), sizeof(type));
	if (!dst.save(out))
		return false;
	return out.good();
}
bool DistrictLoader::load(istream& in) {
	return true;
}