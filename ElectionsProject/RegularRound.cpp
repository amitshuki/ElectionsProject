#include "RegularRound.h"
bool RegularRound::addDistrict(const myString& districtName, const int& rank) {
	District* dst = distList.addDistrictToList(districtName, rank);// Add the district to the Round's list.
	if (dst == nullptr)
		return false;
	for (int i = 0; i < partyList.getLogSize(); i++)
		if (!dst->addPartyToDistrict(partyList[i]->getSN()))// Add all the parties to the new district's voting list
			return false;
	return partyList.addDistrictToParties(dst->getSN(), dst->getRank());// Add the District to the parties list.
}
bool RegularRound::addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
	
	District* dst = this->distList.getDistrictBySN(districtSN);
	return votersBook.addCitizenToList(name, id, birthYear, districtSN, dst) &&// Add citizen to voters book
		dst->addCitizenToDistrict();// Add a citizen to the district's counter
}
bool RegularRound::addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
	Citizen* const rep = votersBook.getCitizenByID(repID);
	Party* const prt = partyList.getPartyBySN(partySN);
	District* const dst = distList.getDistrictBySN(districtSN);
	if (rep && prt && dst)
		return prt->addCitizenAsRep(rep, dst->getSN());
	return false;
}

void RegularRound::showDistrict()const {
	cout << "Districts:" << endl;
	cout << "=========" << endl;
	cout << distList;
}