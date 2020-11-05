#include "ExpandingContainer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv)
{
	try
	{
		ExpandingContainer<int, 5> intContainer{};
		for (int i = 0; i < 40; i++)
		{
			intContainer.Add(i);
		}	


		for (int i = 0; i < intContainer.Size(); i++)
		{
			cout << intContainer[i] << endl;
		}

		cout << "Number of elements: " << intContainer.Size() << endl;

		/*intContainer.DeleteOnIndex(18);
		cout << "Number of elements: " << intContainer.Size() << endl;
		intContainer.DeleteOnIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;
		intContainer.DeleteOnIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;*/
		/*intContainer.DeleteOnIndex(19);
		cout << "Number of elements: " << intContainer.Size() << endl;*/

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
		intContainer.AddAtIndex(42, 378);
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
	
	return 0;
}