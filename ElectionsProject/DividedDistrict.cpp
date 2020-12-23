#include "DividedDistrict.h"

void DividedDistrict::printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties) {
	int i, curElectors;
	Party* curParty;
	cout << "Voting results for " << *this << endl;
	quickSort(electors_for_parties, 0, electors_for_parties.getSize() - 1);// Sort the array
	for (i = electors_for_parties.getSize() - 1; i >= 0; i--) {
		if (electors_for_parties[i].electorsAmount > 0) {
			cout << "This district grants " << electors_for_parties[i].electorsAmount;
			cout << " electors to: " << *(electors_for_parties[i].party->getCandidate()) << endl;
		}
	}
	cout << "===============================================================" << endl;

	for (i = electors_for_parties.getSize() - 1; i >= 0; i--) {
		curParty = electors_for_parties[i].party;
		curElectors = electors_for_parties[i].electorsAmount;
		curParty->printResults(this->districtSN, curElectors);
	}
}

// A utility function to swap two elements  
void DividedDistrict::swap(ElectorsForParty& a, ElectorsForParty& b)
{
	ElectorsForParty t = a;
	a = b;
	b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int DividedDistrict::partition(ElectorsForPartyArr& electors_for_party, const int& low, const int& high)
{
	int pivot = electors_for_party[high].electorsAmount; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (electors_for_party[j].electorsAmount < pivot)
		{
			i++; // increment index of smaller element  
			swap(electors_for_party[i], electors_for_party[j]);
		}
	}
	swap(electors_for_party[i + 1], electors_for_party[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void DividedDistrict::quickSort(ElectorsForPartyArr& electors_for_party, const int& low, const int& high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(electors_for_party, low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(electors_for_party, low, pi - 1);
		quickSort(electors_for_party, pi + 1, high);
	}
}

ElectorsForPartyArr& DividedDistrict::getVotingresults(PartyList& partyList) {
	int i, cur_voters_amount, cur_party_sn;
	float cur_percentage;
	const int num_of_parties = partyList.getLogSize();

	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForPartyArr* electors_for_parties = new ElectorsForPartyArr(partyList);

	// Calculate Electors for each party
	for (i = 0; i < num_of_parties; i++) {
		cur_party_sn = (*electors_for_parties)[i].party->getSN();
		cur_voters_amount = voters4PartyList.getAmountOfVotersByPartySN(cur_party_sn);
		(*electors_for_parties)[i].electorsAmount = calcElectors(cur_voters_amount);
		(*electors_for_parties)[i].votesForParty = cur_voters_amount;
		cur_percentage = static_cast<float>(cur_voters_amount) / static_cast<float>(totalVoters) * 100;
		(*electors_for_parties)[i].precentage = round(cur_percentage);
	}

	
	printResults(-1, *electors_for_parties);

	return *electors_for_parties;
}