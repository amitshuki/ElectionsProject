#pragma once
#include "VotersForParty.h"
#include "myString.h"
using namespace myStr;
class VotersForParty;

class District
{
private:
	int SN, totalCivils, totalVoters, rank; /* total voters - filled only when  round is initiated (init -1)
													  rank - given randomly */
	myString name;
	VotersForParty* votersForParty;
public:
	District(){
		totalCivils = rank = 0;
		SN = totalVoters = -1;
		name = "";
		votersForParty = nullptr;
	}
	District(const myString& newName,const int& newRank,const int& sn){
		SN = sn;
		totalCivils = 0;
		rank = newRank;
		totalVoters = -1;
		name = newName;
		votersForParty = nullptr;
	}

	~District();

	const int& getSN()const { return SN; }
	const int& getRank()const { return rank; }


	friend ostream& operator<<(ostream& out, const District& dst) {
		out << "Serial Number :" << dst.SN << ", ";
		out << "Name :" << dst.name << ", ";
		out << "Electors :" << dst.rank;
		return out;
	}
};

