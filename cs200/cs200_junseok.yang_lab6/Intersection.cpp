/*
 * junseok yang
 * Lab6 - intersection Test & 2D Picking
 * CS200
 * Fall 2019
 */
#include "CS200/Intersection.h"

namespace CS200
{
	////////////
	//2D picking
	bool PointVSAABB(const Point& p, const Rectangle& rect)
	{
        if(p.x>=rect.GetMin().x&&p.x <= rect.GetMax().x&&p.y >= rect.GetMin().y&&p.y <= rect.GetMax().y)
        {
            return true;
        }
        return false;
	}

    bool PointVSCircle(const Point& p, const Circle& circle)
    {
        if (Vector::dot({ (circle.GetCenter().x - p.x), (circle.GetCenter().y - p.y) }, { (circle.GetCenterX() - p.x),(circle.GetCenterY() - p.y) }) > circle.GetRadius()*circle.GetRadius())
        {
            return false;
        }
        if(Vector::dot({ (circle.GetCenter().x - p.x), (circle.GetCenter().y - p.y) }, { (circle.GetCenterX() - p.x),(circle.GetCenterY() - p.y) }) < circle.GetRadius()*circle.GetRadius())
        {
            return true;
        }
        if (Vector::dot({ (circle.GetCenter().x - p.x), (circle.GetCenter().y - p.y) }, { (circle.GetCenterX() - p.x),(circle.GetCenterY() - p.y) }) == circle.GetRadius()*circle.GetRadius())
        {
            return true;
        }
		return false;
	}

	//////////////
	//Intersection
	bool CircleVSCircle(const Circle& circle1, const Circle& circle2)
	{
        int r_Sum = circle1.GetRadius() + circle2.GetRadius();
        int distance = (circle1.GetCenterX() - circle2.GetCenterX())*(circle1.GetCenterX() - circle2.GetCenterX()) + (circle1.GetCenterY() - circle2.GetCenterY()) *(circle1.GetCenterY() - circle2.GetCenterY());
        if(distance <= r_Sum* r_Sum)
	    {
            return true;
        }
		return false;
	}

	bool AABBVSAABB(const Rectangle& rect1, const Rectangle& rect2)
	{
        if((rect1.GetMax().x <= rect2.GetMin().x) || (rect2.GetMax().x <= rect1.GetMin().x))
        {
            if((rect1.GetMax().y <= rect2.GetMin().y) || (rect2.GetMax().y <= rect1.GetMin().y))
            return false;
        }
        return true;
	}

	//Helper function for CircleVSAABB
	float ShortestDistanceSqr(const Point& p, const Edge& edge)
	{
        if (Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(p.x - edge.end.x, p.y - edge.end.y)) < 0)
        {
            return Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(p.x - edge.start.x, p.y - edge.start.y));
        }
        else if (Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y)) > Vector::dot(Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y),Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y)))
        {
            return Vector::dot(Vector(p.x - edge.end.x, p.y - edge.end.y),Vector(p.x - edge.end.x, p.y - edge.end.y));
        }
        else
        {
            return Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(p.x - edge.start.x, p.y - edge.start.y)) 
            - ((Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y)) 
                * Vector::dot(Vector(p.x - edge.start.x, p.y - edge.start.y), Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y))) 
                / static_cast<float>((Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y).x * Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y).x 
                    + Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y).y * Vector(edge.end.x - edge.start.x, edge.end.y - edge.start.y).y)));
        }
	}

	bool CircleVSAABB(const Circle& circle, const Rectangle& rect)
	{
        float left_edge = ShortestDistanceSqr(circle.GetCenter(), { rect.GetTopLeft(), {rect.GetTopLeft().x, rect.GetBottomRight().y } });
        float top_edge = ShortestDistanceSqr(circle.GetCenter(), { rect.GetTopLeft(), {rect.GetBottomRight().x, rect.GetTopLeft().y } });
        float right_edge = ShortestDistanceSqr(circle.GetCenter(), { {rect.GetBottomRight().x, rect.GetTopLeft().y }, rect.GetBottomRight() });
        float bottom_edge = ShortestDistanceSqr(circle.GetCenter(), { rect.GetBottomRight(), {rect.GetTopLeft().x, rect.GetBottomRight().y } });

        if (left_edge <= static_cast<float>(circle.GetRadius()) * static_cast<float>(circle.GetRadius()) 
            || top_edge <= static_cast<float>(circle.GetRadius()) * static_cast<float>(circle.GetRadius())
            || right_edge <= static_cast<float>(circle.GetRadius()) * static_cast<float>(circle.GetRadius())
            || bottom_edge <= static_cast<float>(circle.GetRadius()) * static_cast<float>(circle.GetRadius()))
        {
            return true;
        }
        return false;
	}
}