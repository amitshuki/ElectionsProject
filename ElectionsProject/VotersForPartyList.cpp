#include "VotersForPartyList.h"
using namespace std;

void VotersForPartyList::addParty(const int& partySN) {
	VotersForParty vfp(partySN);
	vfpArr.push_back(vfp);
}
void VotersForPartyList::voteForParty(const int& partySN) {
	for (auto& i : vfpArr) {
		if (i.getPartySN() == partySN) {
			i.addVote();
			return;// important
		}
	}
	//if party was not found - exception!
	throw no_entity_error("VotersforPartyList");
}

const int& VotersForPartyList::getAmountOfVotersByPartySN(const int& partySN) {
	for (auto& i : vfpArr) {
		if (i.getPartySN() == partySN)
			return i.getNumOfVoters();
	}
	throw no_entity_error("VotersforPartyList");
}


VotersForParty& VotersForPartyList::getVFPByPartySN(const int& partySN) {
	for (auto& i : vfpArr)
		if (i.getPartySN() == partySN)
			return i;
	throw no_entity_error("VotersForPartyList");
}

VotersForPartyList& VotersForPartyList::operator=(const VotersForPartyList& other) {
	if (this != &other)
		vfpArr = other.vfpArr;
	return *this;
}

void VotersForPartyList::save(ostream& out) const {
	out.write(rcastcc(&vfpArr.getLogSize()), sizeof(vfpArr.getLogSize()));
	for (auto& i : vfpArr) {
		i.save(out);
		if (!out.good())
			throw outfile_error("VotersForPartyList");
	}
}
void VotersForPartyList::load(istream& in){
	int size;
	in.read(rcastc(&size), sizeof(size));
	DynamicArray<VotersForParty> newArr;
	for (int i = 0; in.good() && i < size; i++) {
		newArr.push_back(VotersForParty(in));
	}
	if(!in.good())
		throw infile_error("VotersForPartyList");

	vfpArr = newArr;
}