#include "DistrictBasedState.h"
bool DistrictBasedState::addDistrict(const myString& districtName, const int& rank, const DistrictType& dt) {
	District* dst = distList.addDistrictToList(districtName, rank, dt);// Add the district to the Round's list.
	if (dst == nullptr)
		return false;
	for (int i = 0; i < partyList.getLogSize(); i++)
		if (!dst->addPartyToDistrict(partyList[i]->getSN()))// Add all the parties to the new district's voting list
			return false;
	return partyList.addDistrictToParties(dst->getSN(), dst->getRank());// Add the District to the parties list.
}
bool DistrictBasedState::addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {

	District* dst = this->distList.getDistrictBySN(districtSN);
	return votersBook.addCitizenToList(name, id, birthYear, districtSN, dst) &&// Add citizen to voters book
		dst->addCitizenToDistrict();// Add a citizen to the district's counter
}
bool DistrictBasedState::addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
	Citizen* const rep = votersBook.getCitizenByID(repID);
	Party* const prt = partyList.getPartyBySN(partySN);
	District* const dst = distList.getDistrictBySN(districtSN);
	if (rep && prt && dst)
		return prt->addCitizenAsRep(rep, dst->getSN());
	return false;
}

void DistrictBasedState::showDistrict()const {
	cout << "Districts:" << endl;
	cout << "=========" << endl;
	cout << distList;
}

bool DistrictBasedState::save(ostream& out)const {
	State::save(out);
	return out.good();
}

bool DistrictBasedState::load(istream& in) {
	State::load(in);
	return in.good();
}