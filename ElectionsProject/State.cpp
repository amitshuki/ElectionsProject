#include "State.h"
Date::Date(const int& d, const int& m, const int& y){
	if (d < 0 || d>31)
		throw range_error("Invalid day.");
	if (m < 0 || m>12)
		throw range_error("Invalid month.");
	if (y < 0 || y>2021)
		throw range_error("Invalid year.");
	if (d > 28 && m == 2)
		throw range_error("Invalid day and month");
	this->day = d;
	this->month = m;
	this->year = y;
}
bool Date::operator==(const Date& other)const {
	if (day == other.day && month == other.month && year == other.year)
		return true;
	return false;
}
ostream& operator<<(ostream& out, const Date& dt) {
	out << dt.day << "\\" << dt.month << "\\" << dt.year;
	return out;
}

State::State(istream& in) :votersBook(RoundMode::REGULAR), partyList(RoundMode::REGULAR) {
	try {
		CitizenList* temp_votersBook = new CitizenList(in);
		if (!temp_votersBook)
			throw bad_alloc();
		DistrictList* temp_distList = new DistrictList(in);
		if (!temp_distList) {
			temp_votersBook->~CitizenList();
			throw bad_alloc();
		}
		PartyList* temp_partyList = new PartyList(in);
		if (!temp_partyList) {
			temp_votersBook->~CitizenList();
			temp_distList->~DistrictList();
			throw bad_alloc();
		}
		votersBook = *temp_votersBook;
		distList = *temp_distList;
		partyList = *temp_partyList;
		in.read(rcastc(&this->hasAny1votedyet), sizeof(this->hasAny1votedyet));
		connectCitizensToDistricts();
		partyList.connectPartyreps2Citizens(votersBook);
	}
	catch (connection_error& cnc_err) {
		cout << cnc_err.what() << endl;
		votersBook.~CitizenList();
		distList.~DistrictList();
		partyList.~PartyList();
	}
	catch (exception& exp) {
		cout << "Error creating State: " << exp.what() << endl;
		votersBook.~CitizenList();
		distList.~DistrictList();
		partyList.~PartyList();
	}
}

void State::addParty(const myString& partyName, const int& candidateId) {
	Citizen* candidate = votersBook.getCitizenByID(candidateId);
	if (!candidate)
		throw no_entity_error("Candidate", "State");
	Party* newParty;
	// Add the party to the State's list
	newParty = partyList.addPartyToList(partyName, candidate);
	if (!newParty)
		throw adding_error("Party", "State");
	for (int i = 0; i < distList.getLogSize(); i++) {
		newParty->addDistrict(distList[i]->getSN(), distList[i]->getRank());//add all of the districts to the new party
		distList[i]->addPartyToDistrict(newParty->getSN());// add the new party to all of the districts
	}
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

void State::vote(const int& id, const int& partySN) {
	try {
		Citizen* cit = votersBook.getCitizenByID(id);
		if (!cit)
			throw no_entity_error("Citizen", "State");
		if (cit->hasVoted())
			throw has_voted_error(cit->getId());
		if (!checkExistingPartyBySN(partySN))
			throw no_entity_error("Party");

		District* dst = cit->getDistrict();
		// Add vote to the party in the district of the citizen.
		dst->addVoteToParty(partySN);

		cit->vote(partySN);
		hasAny1votedyet = true;
	}
	catch (exception& exp) {
		cout << exp.what() << endl;
	}
}

void State::showElectionsResults() {
	try {
		if (this->hasAny1votedyet == false)
			throw elections_result_exception("no one has voted yet.");
		cout << "Date of the elections: " << this->elections_date << endl;
		int winningPartyElectorsAmount;// getResults updates it byRef
		const Party* winningParty = distList.getResults(winningPartyElectorsAmount, partyList);
		cout << "The winner of the elections, with " << winningPartyElectorsAmount << " electors is: " << endl;
		cout << *(winningParty->getCandidate()) << endl;
	}
	catch (exception& exp) {
		cout << exp.what() << endl;
	}
}


void State::save(ostream& out) const {
	votersBook.save(out);
	distList.save(out);
	partyList.save(out);
	out.write(rcastcc(&hasAny1votedyet), sizeof(hasAny1votedyet));
	if (!out.good())
		throw outfile_error("State");
}

void State::load(istream& in) {
	votersBook.load(in);
	distList.load(in);
	partyList.load(in);
	in.read(rcastc(&hasAny1votedyet), sizeof(hasAny1votedyet));
	if (!in.good()) {
		votersBook.~CitizenList();
		distList.~DistrictList();
		partyList.~PartyList();
		throw infile_error("State");
	}
}

void State::connectCitizensToDistricts() {
	Citizen* curCit;
	District* dst;
	int amountOfCitizens = votersBook.getLogSize();
	try {
		for (int i = 0; i < amountOfCitizens; i++) {// Connect every citizen to Districts
			curCit = votersBook[i];
			if (curCit) {
				dst = distList.getDistrictBySN(curCit->getDistrictSN());
				if (dst)
					curCit->setDistrict(dst);
				else
					throw no_entity_error("District", "State");
			}
			else
				throw no_entity_error("Citizen", "State");
		}
	}
	catch (exception& exp) {
		cout << exp.what();
		throw connection_error("Citizens","Districts");// if in exception was thrown - do not connect the list to the partially connected list
	}
}
