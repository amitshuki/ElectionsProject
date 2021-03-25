#include "DistrictLoader.h"

using namespace std;
void DistrictLoader::save(ostream& out,const District& dst) {
	DistrictType type;

	if (typeid(dst) == typeid(DividedDistrict))
		type = DistrictType::DIVIDED;
	else if (typeid(dst) == typeid(UnifiedDistrict))
		type = DistrictType::UNIFIED;
	else
		throw exception("Undefined DistrictType - class DistrictLoader");
	out.write(rcastcc(&type), sizeof(type));
	dst.save(out);
}
District* DistrictLoader::load(istream& in) {
	DistrictType type;
	District* dst;
	in.read(rcastc(&type), sizeof(type));
	switch (type) {
	case DistrictType::DIVIDED:
		dst = new DividedDistrict(in);
		break;
	case DistrictType::UNIFIED:
		dst = new UnifiedDistrict(in);
		break;
	default:
		throw undefined_option("DistrictType");
	}
	if (!dst)
		throw bad_alloc();
	return dst;
}