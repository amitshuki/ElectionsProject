#include "StateLoader.h"
bool StateLoader::save(ostream& out, const State& rnd) {
	StateType rType;
	if (typeid(rnd) == typeid(DistrictBasedState))
		rType = StateType::DISTRICT_BASED;
	else if (typeid(rnd) == typeid(UniformState))
		rType = StateType::UNIFORM;
	out.write(rcastcc(&rType), sizeof(rType));
	rnd.save(out);
	return out.good();
}
State* StateLoader::load(istream& in) {
	StateType type;
	in.read(rcastc(&type), sizeof(type));
	switch (type) {
	case StateType::DISTRICT_BASED:
		return new DistrictBasedState(in);
		break;
	case StateType::UNIFORM:
		return new UniformState(in);
		break;
	}
	return nullptr;
}