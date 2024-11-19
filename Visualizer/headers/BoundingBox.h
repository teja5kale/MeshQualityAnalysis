#pragma once

#include "ModifiedTriangulation.h"

class BoundingBox
{
public:
	double minX(ModifiedTriangulation triangulation);
	double minY(ModifiedTriangulation triangulation);
	double minZ(ModifiedTriangulation triangulation);
	double maxX(ModifiedTriangulation triangulation);
	double maxY(ModifiedTriangulation triangulation);
	double maxZ(ModifiedTriangulation triangulation);
	BoundingBox();
	~BoundingBox();
	void createBoundingBoxTriangulation(ModifiedTriangulation triangulation);
	double boundingBoxArray[24];
};
