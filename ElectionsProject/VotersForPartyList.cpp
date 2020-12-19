#include "VotersForPartyList.h"

void VotersForPartyList::resize() {
	int i;
	if (capacity == 0)
		capacity++;
	VotersForParty* newVfpArr = new VotersForParty[capacity * 2];
	for (i = 0; i < logSize; i++)
		newVfpArr[i] = vfpArr[i];
	delete[] vfpArr;
	vfpArr = newVfpArr;
	capacity *= 2;
}


bool VotersForPartyList::addParty(const int& partySN) {
	if (logSize == capacity)
		resize();
	return vfpArr[logSize++].setPartySN(partySN);
}
bool VotersForPartyList::voteForParty(const int& partySN) {
	int i;
	for (i = 0; i < logSize; i++)
		if (vfpArr[i].getPartySN() == partySN)
			return vfpArr[i].addVote();
	return false;
}

const int& VotersForPartyList::getAmountOfVotersByPartySN(const int& partySN) {
	for (int i = 0; i < logSize; i++)
		if (vfpArr[i].getPartySN() == partySN)
			return vfpArr[i].getNumOfVoters();
	return -1;
}


VotersForParty& VotersForPartyList::getVFPByPartySN(const int& partySN) {
	for (int i = 0; i < logSize; i++)
		if (vfpArr[i].getPartySN() == partySN)
			return vfpArr[i];
}

const VotersForParty& VotersForPartyList::operator[](const int idx) {
	if (idx >= 0 && idx < logSize)
		return vfpArr[idx];
	std::cout << "Index out of range." << std::endl;
}
VotersForPartyList& VotersForPartyList::operator=(const VotersForPartyList& other) {
	VotersForParty* newVfpArr = new VotersForParty[other.logSize];
	for (int i = 0; i < other.logSize; i++)
		newVfpArr[i] = other.vfpArr[i];
	delete[] vfpArr;
	vfpArr = newVfpArr;
	logSize = capacity = other.logSize;
	return *this;
}