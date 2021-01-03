#include "UniformState.h"
using namespace std;
UniformState::UniformState(const int& rank) :State(RoundMode::SIMPLE) {
	District* dst = this->distList.addDistrictToList("gen_dst", rank, DistrictType::UNIFIED);
	this->districtSN = dst->getSN();
}

bool UniformState::addCitizen(const myString& name, const int& id, const int& birthYear) {
	District* dst = this->distList.getDistrictBySN(districtSN);
	return votersBook.addCitizenToList(name, id, birthYear, districtSN, dst) &&// Add citizen to voters book
		dst->addCitizenToDistrict();// Add a citizen to the district's counter
}

bool UniformState::addCitizenAsPartyRep(const int& repID, const int& partySN) {
	Citizen* const rep = votersBook.getCitizenByID(repID);
	Party* const prt = partyList.getPartyBySN(partySN);
	if (rep && prt)
		return prt->addCitizenAsRep(rep, this->districtSN);
	return false;
}

bool UniformState::save(ostream& out)const {
	State::save(out);
	out.write(rcastcc(&this->districtSN), sizeof(this->districtSN));
	return out.good();
}

bool UniformState::load(istream& in) {
	return true;
}