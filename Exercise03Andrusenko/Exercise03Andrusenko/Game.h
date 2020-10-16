#pragma once
#include "Object.h"
#include "MovableObject.h"

class Game
{
	Object** objects;
public:
	Game(Object** objects);
	~Game();
	void AddObject(Object* o);
	int* FindIdsOfStaticObjectsInXY(double xmin, double xmax, double ymin, double ymax);
	MovableObject** FindMovableObjectsInArea(double x, double y, double r);
	MovableObject** FindMovableObjectsInAreaWithAngle(double x, double y, double r, double umin, double umax);
};

