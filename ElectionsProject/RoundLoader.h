#pragma once
#include "Round.h"
#include "RegularRound.h"
#include "SimpleRound.h"

enum class RoundType { REGULAR, SIMPLE};
class RoundLoader
{
	static bool save(ostream& out, const Round& rnd);
	static bool load(istream& in);
};