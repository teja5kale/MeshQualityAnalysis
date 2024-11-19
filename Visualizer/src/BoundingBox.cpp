#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

double BoundingBox::minX(ModifiedTriangulation triangulation)
{
    double minX = std::numeric_limits<double>::infinity();

    for (ModifiedTriangle triangle : triangulation.mTriangles) {
        if (triangle.P1().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P1().X()];
        }
        if (triangle.P2().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P2().X()];
        }
        if (triangle.P3().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P3().X()];
        }
    }
    return minX;
}

double BoundingBox::minY(ModifiedTriangulation triangulation)
{
    double minY = std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P2().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P2().Y()];
        }
        if (vertex.P3().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P3().Y()];
        }
    }
    return minY;
}

double BoundingBox::minZ(ModifiedTriangulation triangulation)
{
    double minZ = std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P2().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P2().Z()];
        }
        if (vertex.P3().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P3().Z()];
        }
    }
    return minZ;
}

double BoundingBox::maxX(ModifiedTriangulation triangulation)
{
    double maxX = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
        if (vertex.P2().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
        if (vertex.P3().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
    }
    return maxX;
}

double BoundingBox::maxY(ModifiedTriangulation triangulation)
{
    double maxY = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P2().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P3().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
    }
    return maxY;
}

double BoundingBox::maxZ(ModifiedTriangulation triangulation)
{
    double maxZ = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P2().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P3().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
    }
    return maxZ;
}

void BoundingBox::createBoundingBoxTriangulation(ModifiedTriangulation triangulation)
{
    ModifiedTriangulation modifiedTriangulation;

    modifiedTriangulation._minX = minX(triangulation);
    modifiedTriangulation._minY = minY(triangulation);
    modifiedTriangulation._minZ = minZ(triangulation);
    modifiedTriangulation._maxX = maxX(triangulation);
    modifiedTriangulation._maxY = maxY(triangulation);
    modifiedTriangulation._maxZ = maxZ(triangulation);

    boundingBoxArray[0] = modifiedTriangulation._minX;
	boundingBoxArray[1] = modifiedTriangulation._minY;
	boundingBoxArray[2] = modifiedTriangulation._minZ;
	boundingBoxArray[3] = modifiedTriangulation._maxX;
	boundingBoxArray[4] = modifiedTriangulation._minY;
	boundingBoxArray[5] = modifiedTriangulation._minZ;
	boundingBoxArray[6] = modifiedTriangulation._maxX;
	boundingBoxArray[7] = modifiedTriangulation._maxY;
	boundingBoxArray[8] = modifiedTriangulation._minZ;
	boundingBoxArray[9] = modifiedTriangulation._minX;
	boundingBoxArray[10] = modifiedTriangulation._maxY;
	boundingBoxArray[11] = modifiedTriangulation._minZ;
	boundingBoxArray[12] = modifiedTriangulation._minX;
	boundingBoxArray[13] = modifiedTriangulation._minY;
	boundingBoxArray[14] = modifiedTriangulation._maxZ;
	boundingBoxArray[15] = modifiedTriangulation._maxX;
	boundingBoxArray[16] = modifiedTriangulation._minY;
	boundingBoxArray[17] = modifiedTriangulation._maxZ;
	boundingBoxArray[18] = modifiedTriangulation._maxX;
	boundingBoxArray[19] = modifiedTriangulation._maxY;
	boundingBoxArray[20] = modifiedTriangulation._maxZ;
	boundingBoxArray[21] = modifiedTriangulation._minX;
	boundingBoxArray[22] = modifiedTriangulation._maxY;
	boundingBoxArray[23] = modifiedTriangulation._maxZ;
}
