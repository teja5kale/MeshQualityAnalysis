#pragma once
#include<string>
#include "ModifiedTriangulation.h"

using namespace Geometry;

class Reader
{
	virtual void read(const std::string& fileName, ModifiedTriangulation& triangulation) = 0;
};
