#include "VotersForPartyList.h"
using namespace std;

bool VotersForPartyList::addParty(const int& partySN) {
	VotersForParty vfp(partySN);
	vfpArr1.push_back(vfp);
	return true;//Needs to change..
}
bool VotersForPartyList::voteForParty(const int& partySN) {
	for (auto& i : vfpArr1)
		if (i.getPartySN() == partySN)
			return i.addVote();
	return false;
}

const int& VotersForPartyList::getAmountOfVotersByPartySN(const int& partySN) {
	for (auto& i : vfpArr1)
		if (i.getPartySN() == partySN)
			return i.getNumOfVoters();
	return -1;// Party Not found - exeption!!!
}


VotersForParty& VotersForPartyList::getVFPByPartySN(const int& partySN) {
	for (auto& i : vfpArr1)
		if (i.getPartySN() == partySN)
			return i;
}

VotersForPartyList& VotersForPartyList::operator=(const VotersForPartyList& other) {
	vfpArr1 = other.vfpArr1;
	return *this;
}

bool VotersForPartyList::save(ostream& out) const {
	out.write(rcastcc(&vfpArr1.getLogSize()), sizeof(vfpArr1.getLogSize()));
	for (auto& i : vfpArr1)
		if (!i.save(out))
			return false;
	return out.good();
}
bool VotersForPartyList::load(istream& in){
	int size;
	in.read(rcastc(&size), sizeof(size));
	DynamicArray<VotersForParty> newArr;
	for (int i = 0; in.good() && i < size; i++)
		newArr.push_back(VotersForParty(in));

	vfpArr1 = newArr;

	return in.good();
}