#pragma once

#include "ModifiedTriangulation.h"

namespace QualityAnalysis 
{
	class QualityAnalysis
	{
		std::vector<double> convertToNegativePoint(std::vector<double> point);
		std::vector<double> convertPointToVector(Geometry::Point point, ModifiedTriangulation triangulation);
		double clamp(double value, double min, double max);
		double calculateDistanceBetweenPoints(std::vector<double> firstPoint, std::vector<double> secondPoint);
		double calculateAngleBetweenVectors(std::vector<double> v1, std::vector<double> v2);
		double calculateSingleTriangleAspectRatio(ModifiedTriangle& triangle, ModifiedTriangulation triangulation);
		double calculateSingleTriangleInteriorAngle(Geometry::Point p1, Geometry::Point p2, Geometry::Point p3, ModifiedTriangulation triangulation);
		double calculateSingleTriangleArea(ModifiedTriangle& triangle, ModifiedTriangulation triangulation);
		std::vector<double> calcuateSingleTriangleNormal(std::vector<double> v1, std::vector<double> v2, std::vector<double> v3);
	public:
		QualityAnalysis();
		~QualityAnalysis();
		double caculateTotalsurfaceArea(ModifiedTriangulation triangulation);
		double triangleDensity(ModifiedTriangulation triangulation);
		double objectLength(ModifiedTriangulation triangulation);
		double objectBreadth(ModifiedTriangulation triangulation);
		double objectHeight(ModifiedTriangulation triangulation);
		size_t numberOfTriangles(ModifiedTriangulation triangulation);
		size_t numberOfVertices(ModifiedTriangulation triangulation);
		ModifiedTriangulation createOrthogonalityTriangulation(ModifiedTriangulation triangulation);
		ModifiedTriangulation createAspectRatioTriangulation(ModifiedTriangulation triangulation);
	};
}
