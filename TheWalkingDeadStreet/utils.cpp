#include "stdafx.h"
#include "utils.h"


utils::utils()
{
}


utils::~utils()
{
}

bool utils::isCompatible(vector<Tourelle> shooterPosition, vector<int> tower)
{
	if (shooterPosition.size() != NULL) {
		for (vector<Tourelle>::iterator shooter = shooterPosition.begin(); shooter != shooterPosition.end(); ++shooter) {
			for (vector<int>::iterator place = tower.begin(); place != tower.end(); ++place) {
				if (shooter->getPosition() == *place) {
					return false;
				}
			}
		}
	}
	return true;
}

bool utils::Sort_by_est(Tourelle & a, Tourelle & b)
{
	return a.getEstimation() < b.getEstimation();
}

bool utils::Sort_by_dist(Tourelle & a, Tourelle & b)
{
	return a.getDistance() < b.getDistance();
}