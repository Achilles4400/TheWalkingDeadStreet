#include "stdafx.h"
#include "Tourelle.h"


Tourelle::Tourelle(int distance, int estimation, int position)
{
	this->distance = distance;
	this->estimation = estimation;
	this->position = position;
}


Tourelle::~Tourelle()
{
}

string Tourelle::toString()
{
	return  "distance: " + to_string(this->distance) + " estimation: " + to_string(this->estimation) + " position: " + to_string(this->position);
}
