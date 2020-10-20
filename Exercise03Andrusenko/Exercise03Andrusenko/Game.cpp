#include <iostream>
#include <exception>

#include "Game.h"
#include "StaticObject.h"

using namespace std;

Game::Game(int size)
{
	this->size = size;
	this->objects = new Object* [size];
	counterObjects = 0;	
}

Game::~Game()
{
	delete[] objects;
}

void Game::AddObject(Object* o)
{
	if (counterObjects == size)
	{
		throw out_of_range("Array is full!");
	}
	
	objects[counterObjects++] = o;	
}

int* Game::FindIdsOfStaticObjectsInXY(double xmin, double xmax, double ymin, double ymax)
{
	int* ids = new int[counterObjects];
	int countIds = 0;
	for (int i = 0; i < counterObjects; i++)
	{
		if (dynamic_cast<StaticObject*>(objects[i]) != nullptr)
		{
			if (objects[i]->GetX() >= xmin && objects[i]->GetX() <= xmax && objects[i]->GetY() >= ymin && objects[i]->GetY() <= ymax)
			{
				ids[++countIds] = objects[i]->GetId();
			}
		}
		
	}

	ids[0] = countIds;

	if (countIds != 0)
	{
		return ids;
	}

	delete[] ids;
	return 0;
}

MovableObject** Game::FindMovableObjectsInArea(double x, double y, double r)
{	
	MovableObject** mObjects = new MovableObject*[counterObjects];
	int counterMO = 0;
	for (int i = 0; i < counterObjects; i++)
	{
		if (dynamic_cast<MovableObject*>(objects[i]) != nullptr) {
			double distanceToPoint = sqrt((pow(x - objects[i]->GetX(), 2)) + pow(y - objects[i]->GetY(), 2));			
			if (distanceToPoint <= r) {
				mObjects[counterMO++] = dynamic_cast<MovableObject*>(objects[i]);
			}
		}
	}

	if (counterMO != 0)
	{
		MovableObject** mObjectsCopy = new MovableObject * [counterMO];
		for (int i = 0; i < counterMO; i++)
		{
			mObjectsCopy[i] = mObjects[i];
		}
		delete[] mObjects;
		return mObjectsCopy;
	}

	delete[] mObjects;
	return nullptr;
}

MovableObject** Game::FindMovableObjectsInAreaWithAngle(double x, double y, double r, double umin, double umax)
{	
	MovableObject** mObjects = new MovableObject * [counterObjects];
	int counterMO = 0;
	for (int i = 0; i < sizeof(objects); i++)
	{
		if (dynamic_cast<MovableObject*>(objects[i]) != nullptr) {
			double distanceToPoint = sqrt((pow(x - objects[i]->GetX(), 2)) + pow(y - objects[i]->GetY(), 2));
			if (distanceToPoint <= r && dynamic_cast<MovableObject*>(objects[i])->GetDirectionAngle() >= umin &&
				dynamic_cast<MovableObject*>(objects[i])->GetDirectionAngle() <= umax) {
				mObjects[counterMO++] = dynamic_cast<MovableObject*>(objects[i]);
			}
		}
	}

	if (counterMO != 0)
	{
		MovableObject** mObjectsCopy = new MovableObject * [counterMO];
		for (int i = 0; i < counterMO; i++)
		{
			mObjectsCopy[i] = mObjects[i];
		}
		delete[] mObjects;
		return mObjectsCopy;
	}

	delete[] mObjects;
	return nullptr;
}
