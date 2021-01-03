#include "State.h"

bool Date::operator==(const Date& other)const {
	if (day == other.day && month == other.month && year == other.year)
		return true;
	return false;
}
ostream& operator<<(ostream& out, const Date& dt) {
	out << dt.day << "\\" << dt.month << "\\" << dt.year;
	return out;
}


State::State(istream& in) :votersBook(in), distList(in), partyList(in) {
	in.read(rcastc(&hasAny1votedyet), sizeof(hasAny1votedyet)); 
	connectCitizensToDistricts();
	partyList.connectPartyreps2Citizens(votersBook);
}

bool State::addParty(const myString& partyName, const int& candidateId) {
	Citizen* const candidate = votersBook.getCitizenByID(candidateId);
	Party* newParty;
	bool res = false;
	if (!candidate) 
		return false;
	else {
		// Add the party to the State's list
		newParty = partyList.addPartyToList(partyName, candidate);
		if (newParty != nullptr) {
			for (int i = 0; i < distList.getLogSize(); i++) {
				//add all of the districts to the new party
				res = newParty->addDistrict(distList[i]->getSN(), distList[i]->getRank());
				// add the new party to all of the districts
				res = distList[i]->addPartyToDistrict(newParty->getSN());
				if (!res)
					break;
			}
		}
	}
	return res;
}

void State::showVotersBook()const {
	cout << "Voters Book:" << endl;
	cout << "===========" << endl;
	cout << votersBook;
}

void State::showParties()const {
	cout << "Parties:" << endl;
	cout << "=======" << endl;
	cout << partyList;
}

bool State::vote(const int& id, const int& partySN) {
	Citizen* cit = votersBook.getCitizenByID(id);
	if (!cit->hasVoted()) {
		hasAny1votedyet = true;
		cit->vote(partySN);
	}

	// Add vote to the party in the district of the citizen.
	District* dst = cit->getDistrict();
	if (!dst->addVoteToParty(partySN))
		return false;
	return true;
}

void State::showElectionsResults() {
	if (this->hasAny1votedyet == false)
		return;
	cout << "Date of the elections: " << date << endl;
	int winningPartyElectorsAmount;// getResults updates it byRef
	Party* winningParty = distList.getResults(winningPartyElectorsAmount, partyList);
	cout << "The winner of the elections, with " << winningPartyElectorsAmount << " electors is: " << endl;
	cout << *(winningParty->getCandidate()) << endl;
}

bool State::setDate(const int& d, const int& m, const int& y) {
	Date dt(d, m, y);
	this->date = dt;
	return this->date == dt;
}

bool State::save(ostream& out) const {
	if (!votersBook.save(out) || !distList.save(out) || !partyList.save(out))
		return false;
	out.write(rcastcc(&hasAny1votedyet), sizeof(hasAny1votedyet));
	return out.good();
}

bool State::load(istream& in) {
	if (!votersBook.load(in) || !distList.load(in) || !partyList.load(in))
		return false;
	in.read(rcastc(&hasAny1votedyet), sizeof(hasAny1votedyet));
	return in.good();
}

bool State::connectCitizensToDistricts() {
	Citizen* curCit;
	District* dst;
	int amountOfCitizens = votersBook.getLogSize(), i;
	for (i = 0; i < amountOfCitizens; i++) {// Connect every citizen to Districts
		curCit = votersBook[i];
		if (curCit) {
			dst = distList.getDistrictBySN(curCit->getDistrictSN());
			if (dst)
				curCit->setDistrict(dst);
			else
				return false;
		}
		else
			return false;
	}
	return true;
}
