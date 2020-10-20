#ifndef GAME_H
#define GAME_H

#include "Object.h"
#include "MovableObject.h"

class Game
{
	Object** objects;
	int counterObjects;
	int size;
public:
	Game(int size);	
	~Game();
	void AddObject(Object* o);
	int* FindIdsOfStaticObjectsInXY(double xmin, double xmax, double ymin, double ymax);
	MovableObject** FindMovableObjectsInArea(double x, double y, double r);
	MovableObject** FindMovableObjectsInAreaWithAngle(double x, double y, double r, double umin, double umax);
};

#endif // !GAME_H



