#include <iostream>
#include <sstream>
#include <time.h>

#include "PhoneList.h"

using namespace Entity;
using namespace Model;
using namespace std;

int main(int argc, char* argv)
{
	PhoneList* phoneList = new PhoneList();
	try
	{		
		srand(time(NULL));
		Person p1{"Andrii", "1111111" };
		Person p2{"Marta", "2222222" };
		Person p3{"Sara", "3333333" };
		phoneList->AddPerson(p1);
		phoneList->AddPerson(p2);
		phoneList->AddPerson(p3);

		for (int i = 4; i < 1000; i++)
		{
			std::ostringstream os1;
			std::ostringstream os2;
			os1 << "Person" << i;
			os2 << rand() % 100000;
			phoneList->AddPerson(Person{ os1.str(), os2.str() });
		}	
		

		cout << phoneList->FindPhoneNumberById(999) << endl;
		cout << phoneList->FindPhoneNumberByName("Sara") << endl;
		delete phoneList;
	}
	catch (exception e)
	{
		delete phoneList;
		cerr << e.what() << endl;
	}
	
	return 0;
}