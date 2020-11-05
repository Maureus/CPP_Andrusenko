#include "ExpandingContainer.h"
#include <iostream>
#include <sstream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(int argc, char* argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{		
		ExpandingContainer<int, 5, 2> intContainer{};
		for (int i = 0; i < 40; i++)
		{
			intContainer.Add(i);
		}	


		for (int i = 0; i < intContainer.Size(); i++)
		{
			cout << intContainer[i] << endl;
		}

		cout << "Number of elements: " << intContainer.Size() << endl;

		intContainer.DeleteAtIndex(18);
		cout << "Number of elements: " << intContainer.Size() << endl;
		intContainer.DeleteAtIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;
		intContainer.DeleteAtIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;
		intContainer.DeleteAtIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;

		/*for (int i = 0; i < intContainer.Size(); i++)
		{
			cout << intContainer[i] << endl;
		}

		cout << "Number of elements: " << intContainer.Size() << endl;*/

		intContainer.AddAtIndex(11, 378);
		intContainer.AddAtIndex(16, 378);
		intContainer.DeleteAtIndex(16);
		for (int i = 0; i < intContainer.Size(); i++)
		{
			cout << intContainer[i] << endl;
		}

		cout << "Number of elements: " << intContainer.Size() << endl;
		//intContainer.AddAtIndex(42, 378);
		

		ExpandingContainer<string, 5, 2> strContainer{};
		for (int i = 0; i < 40; i++)
		{
			std::ostringstream os;
			os << "string" << i;
			strContainer.Add(os.str());
			cout << strContainer[i] << endl;
		}			
		
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}	

	_CrtDumpMemoryLeaks();
	
	return 0;
}