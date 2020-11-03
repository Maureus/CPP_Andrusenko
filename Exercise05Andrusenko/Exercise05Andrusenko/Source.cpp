#include <iostream>

#include "PhoneList.h"

using namespace Entity;
using namespace Model;
using namespace std;

int main(int argc, char* argv)
{
	Person p1{ 1, "Andrii", "1111111" };
	Person p2{ 2, "Marta", "2222222" };
	Person p3{ 3, "Sara", "3333333" };
	PhoneList* phoneList = new PhoneList();
	phoneList->AddPerson(p1);
	phoneList->AddPerson(p2);
	phoneList->AddPerson(p3);

	cout << phoneList->FindPhoneNumberById(1) << endl;
	cout << phoneList->FindPhoneNumberByName("Sara") << endl;

	delete phoneList;
	return 0;
}