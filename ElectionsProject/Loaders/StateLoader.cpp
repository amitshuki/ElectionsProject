#include "StateLoader.h"
void StateLoader::save(ostream& out, const State& rnd) {
	StateType rType;
	if (typeid(rnd) == typeid(DistrictBasedState))
		rType = StateType::DISTRICT_BASED;
	else if (typeid(rnd) == typeid(UniformState))
		rType = StateType::UNIFORM;
	else
		throw exception("Undefined State Type - class StateLoader");
	out.write(rcastcc(&rType), sizeof(rType));
	rnd.save(out);
}
State* StateLoader::load(istream& in) {
	StateType type;
	State* state;
	in.read(rcastc(&type), sizeof(type));
	switch (type) {
	case StateType::DISTRICT_BASED:
		state = new DistrictBasedState(in);
		break;
	case StateType::UNIFORM:
		state = new UniformState(in);
		break;
	default:
		throw undefined_option("Statetype");
	}
	if (!state)
		throw bad_alloc();
	return state;
}