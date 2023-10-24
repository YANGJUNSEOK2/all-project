/*
 * junseok yang
 * Lab7 - Clipping
 * CS200
 * Fall 2019
 */
#include "CS200/Clipping.h"

void Clip(std::vector<Point>& vertices, const ViewportCoord& viewport)
{
    Edge edge = { 0,0 };
    Point Intersection;
    Point endPoint;
    EdgeType type;
    std::vector<Point> vertexTMP;
    vertexTMP = vertices;

    const Boundary BOUNDARY_SIZE[] = { Boundary::Left, Boundary::Right, Boundary::Up, Boundary::Down };

    for(const auto& boundarySize : BOUNDARY_SIZE)
    {
        vertexTMP.clear();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            if (i == vertices.size() - 1)
            {
                edge = { vertices.at(i), vertices.at(0) };
                endPoint = vertices.at(0);
            }
            else
            {
                edge = { vertices.at(i), vertices.at(i + 1) };
                endPoint = vertices.at(i + 1);
            }

            type = edge.GetIntersection(Intersection, boundarySize, viewport);

            if (EdgeType::IN_TO_IN == type)
            {
                vertexTMP.push_back(endPoint);
            }
            else if (EdgeType::IN_TO_OUT == type)
            {
                vertexTMP.push_back(Intersection);
            }
            else if (EdgeType::OUT_TO_IN == type)
            {
                vertexTMP.push_back(Intersection);
                vertexTMP.push_back(endPoint);
            }
            else if (EdgeType::OUT_TO_OUT == type)
            {
                //save none
            }
        }
        vertices = vertexTMP;
    }
}