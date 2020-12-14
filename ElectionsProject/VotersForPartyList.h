#pragma once
#include <iostream>
#include "VotersForParty.h"
class VotersForPartyList
{
private:
	VotersForParty* vfpArr;
	int logSize, capacity;
	
	void resize() {
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
public:
	VotersForPartyList() :logSize(0), capacity(0), vfpArr(nullptr) {}
	~VotersForPartyList() {
		delete[] vfpArr;
	}

	const int& getLogSize()const { return logSize; }

	bool addParty(const int& partySN) {
		if (logSize == capacity)
			resize();
		return vfpArr[logSize++].setPartySN(partySN);
	}
	bool voteForParty(const int& partySN) {
		int i;
		for (i = 0; i < logSize; i++)
			if (vfpArr[i].getPartySN() == partySN)
				return vfpArr[i].addVote();
		return false;
	}

	VotersForParty& getVFPByPartySN(const int& partySN) {
		for (int i = 0; i < logSize; i++)
			if (vfpArr[i].getPartySN() == partySN) 
					return vfpArr[i];
	}

	const VotersForParty& operator[](const int idx) {
		if (idx >= 0 && idx < logSize)
			return vfpArr[idx];
		std::cout << "Index out of range." << std::endl;
	}
	VotersForPartyList& operator=(const VotersForPartyList& other) {
		VotersForParty* newVfpArr = new VotersForParty[other.logSize];
		for (int i = 0; i < other.logSize; i++)
			newVfpArr[i] = other.vfpArr[i];
		delete[] vfpArr;
		vfpArr = newVfpArr;
		logSize = capacity = other.logSize;
	}
};

