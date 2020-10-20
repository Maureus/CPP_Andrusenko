#include <iostream>
#include <exception>

#include "Object.h"
#include "StaticObject.h"
#include "Obstacle.h"
#include "MovableObject.h"
#include "Game.h"


using namespace std;
#define LOG(x) std::cout << x << endl

int main(int agrc, char** argv)
{
	try
	{
		Game* game = new Game(30);
		Object* so1 = new StaticObject{ 1, Obstacle::SmallPlant };
		so1->SetX(2.0);
		so1->SetY(2.0);
		Object* so2 = new StaticObject{ 2, Obstacle::SmallPlant };
		so2->SetX(7.0);
		so2->SetY(3.0);
		Object* so3 = new StaticObject{ 3, Obstacle::SmallPlant };
		so3->SetX(4.0);
		so3->SetY(3.0);	
		Object* mo4 = new MovableObject{ 4 };
		mo4->SetX(2.0);
		mo4->SetY(3.0);		
		MovableObject* mo4m = dynamic_cast<MovableObject*>(mo4);
		mo4m->SetDirectionAngle(15.0);
		Object* mo5 = new MovableObject{ 5 };
		mo5->SetX(2.0);
		mo5->SetY(3.0);
		MovableObject* mo5m = dynamic_cast<MovableObject*>(mo5);
		mo5m->SetDirectionAngle(25.0);

		game->AddObject(so1);
		game->AddObject(so2);
		game->AddObject(so3);
		game->AddObject(mo4);
		game->AddObject(mo5);

		int* sos = game->FindIdsOfStaticObjectsInXY(1.0, 5.0, 1.0, 5.0);
		cout << "Ids: " << endl;
		for (int i = 1; i <= sos[0]; i++)
		{
			LOG(sos[i]);
		}
		MovableObject** mos = game->FindMovableObjectsInArea(1.0, 5.0, 5.0);
		MovableObject* m1 = mos[0];
		MovableObject* m2 = mos[1];

		MovableObject** mos2 = game->FindMovableObjectsInAreaWithAngle(1.0, 5.0, 5.0, 14.0, 20.0);
		MovableObject* m3 = mos2[0];
		MovableObject* m4 = mos2[1];

		Object* object = new StaticObject{ 1, Obstacle::SmallPlant };
		StaticObject* so = dynamic_cast<StaticObject*>(object);
		if (so != nullptr)
		{
			cout << "objekt je StatickyObjekt(nebo jeho potomek)" << endl;
		}

		delete so1;
		delete so2;
		delete so3;
		delete mo4;
		delete mo5;
		delete object;
		game->~Game();
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}
	

	
	return 0;
}