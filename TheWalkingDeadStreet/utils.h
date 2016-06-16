#pragma once

#include "Tourelle.h"

#include <vector>

class utils
{
public:
	utils();
	~utils();
	static bool isCompatible(vector<Tourelle> shooterPosition, vector<int> tower);
	static bool Sort_by_est(Tourelle& a, Tourelle& b);
	static bool Sort_by_dist(Tourelle& a, Tourelle& b);
};

