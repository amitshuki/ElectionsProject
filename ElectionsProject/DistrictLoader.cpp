#include "DistrictLoader.h"

using namespace std;
bool DistrictLoader::save(ostream& out,const District& dst) {
	DistrictType type;
	if (typeid(dst) == typeid(DividedDistrict))
		type = DistrictType::DIVIDED;
	else if(typeid(dst)==typeid(UnifiedDistrict))
		type = DistrictType::UNIFIED;

	out.write(rcastcc(&type), sizeof(type));
	bool b = dst.save(out);
	return b;
}
District* DistrictLoader::load(istream& in) {
	DistrictType type;
	in.read(rcastc(&type), sizeof(type));
	switch (type) {
	case DistrictType::DIVIDED:
		return new DividedDistrict(in);
		break;
	case DistrictType::UNIFIED:
		return new UnifiedDistrict(in);
		break;
	}
	return nullptr;
}