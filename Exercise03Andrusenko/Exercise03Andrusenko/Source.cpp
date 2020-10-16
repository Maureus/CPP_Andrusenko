#include <iostream>
#include "Object.h"
#include "StaticObject.h"
#include "Obstacle.h"
#include "MovableObject.h"

using namespace std;

int main(int agrc, char** argv)
{
	Object f1(1);
	cout << f1.GetId() << endl;
	StaticObject so1(2, Obstacle::BigPlant);
	cout << so1.GetId() << endl;
	so1.SetX(1.0);
	so1.SetY(2.0);
	cout << "X: " << so1.GetX() << endl;
	cout << "Y: " << so1.GetY() << endl;
	MovableObject mo1(3);
	mo1.SetRotationAngle(15.0);
	cout << "mo1: " << mo1.GetId() << ", angle:"<< mo1.GetRotationAngle() <<endl;



	return 0;
}