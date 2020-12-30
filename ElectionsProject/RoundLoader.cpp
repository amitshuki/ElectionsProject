#include "RoundLoader.h"
bool RoundLoader::save(ostream& out, const Round& rnd) {
	RoundType rType;
	if (typeid(rnd) == typeid(RegularRound))
		rType = RoundType::REGULAR;
	else if (typeid(rnd) == typeid(SimpleRound))
		rType = RoundType::SIMPLE;
	out.write(rcastcc(&rType), sizeof(rType));
	
	return out.good();
}
bool RoundLoader::load(istream& in) {
	return true;
}