#include "UniformState.h"
using namespace std;
UniformState::UniformState(const int& rank) :State(RoundMode::SIMPLE) {
	District* dst = this->distList.addDistrictToList("gen_dst", rank, DistrictType::UNIFIED);
	if (!dst) {
		throw exception("Could not add dst to UniformState Ctor");
	}
	this->districtSN = dst->getSN();
}

void UniformState::addCitizen(const string& name, const int& id, const int& birthYear) {
	District* dst = this->distList.getDistrictBySN(districtSN);
	if (!dst)
		throw no_entity_error("District", "UniformState");
	votersBook.addCitizenToList(name, id, birthYear, districtSN, dst);// Add citizen to voters book
	dst->addCitizenToDistrict();// Add a citizen to the district's counter
}

void UniformState::addCitizenAsPartyRep(const int& repID, const int& partySN) {
	Citizen* rep = votersBook.getCitizenByID(repID);
	if (!rep)
		throw no_entity_error("Citizen", "UniformState");
	Party* prt = partyList.getPartyBySN(partySN);
	if (!prt)
		throw no_entity_error("Party", "UniformState");

	prt->addCitizenAsRep(rep, this->districtSN);
}

void UniformState::save(ostream& out)const {
	State::save(out);
	out.write(rcastcc(&this->districtSN), sizeof(this->districtSN));
	if (!out.good())
		throw outfile_error("UniformState");
}
