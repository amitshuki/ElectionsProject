#include "DistrictBasedState.h"
void DistrictBasedState::addDistrict(const myString& districtName, const int& rank, const DistrictType& dt) {
	District* dst = distList.addDistrictToList(districtName, rank, dt);// Add the district to the Round's list.
	if (dst == nullptr)
		throw adding_error("District","DistrictBasedState");
	for (int i = 0; i < partyList.getLogSize(); i++) {
		dst->addPartyToDistrict(partyList[i]->getSN());// Add all the parties to the new district's voting list
	}
	partyList.addDistrictToParties(dst->getSN(), dst->getRank());// Add the District to the parties list.
}

void DistrictBasedState::addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {

	District* dst = this->distList.getDistrictBySN(districtSN);
	if (!dst)
		throw no_entity_error("District in DistrictBasedState");

	votersBook.addCitizenToList(name, id, birthYear, districtSN, dst);// Add citizen to voters book
	dst->addCitizenToDistrict();// Add a citizen to the district's counter
}
void DistrictBasedState::addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
	Citizen* rep = votersBook.getCitizenByID(repID);
	Party* prt = partyList.getPartyBySN(partySN);
	District* dst = distList.getDistrictBySN(districtSN);
	if (!rep)
		throw no_entity_error("Rep", "DistrictBasedState");
	if (!prt)
		throw no_entity_error("Party", "DistrictBasedState");
	if (!dst)
		throw no_entity_error("District", "DistrictBasedState");
	try {
		prt->addCitizenAsRep(rep, dst->getSN());
	}
	catch (exception& exp) {
		cout << "Failed to add rep: " << exp.what() << endl;
	}
}

void DistrictBasedState::showDistrict()const {
	cout << "Districts:" << endl;
	cout << "=========" << endl;
	cout << distList;
}
