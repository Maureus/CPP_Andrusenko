#include "ExpandingContainer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv)
{
	ExpandingContainer<int, 5> intContainer{};
	for (int i = 0; i < 22; i++)
	{
		intContainer.Add(i);
	}

	for (int i = 0; i < intContainer.Size(); i++)
	{
		cout << intContainer[i] << endl;
	}	
	
	return 0;
}