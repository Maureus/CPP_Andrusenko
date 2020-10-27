#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

vector<IComparable*> sort(vector<IComparable*> timeVector)
{

	if (timeVector.size() > 0) {
		int i, j, minIndx;
		for (i = 0; i < timeVector.size() - 1; i++)
		{
			minIndx = i;
			for (j = i + 1; j < timeVector.size(); j++)
				if (timeVector.at(j)->CompareTo(timeVector.at(minIndx)) == -1)
					minIndx = j;

			IComparable* temp = timeVector.at(minIndx);
			timeVector.at(minIndx) = timeVector.at(i);
			timeVector.at(i) = temp;
		}
	}
	
	return timeVector;
}

int main(int argc, char* argv)
{
	try {		
		int n = 10;
		vector<IComparable*> timeVector (n);
		for (int i = 0; i < n; i++)
		{
			timeVector.at(i) = new Time(rand() % 25, rand() % 60, rand() % 60);			
			cout << timeVector.at(i)->ToString() << endl;
		}

		cout << "---------------" << endl;

		timeVector = sort(timeVector);

		for (int i = 0; i < n; i++)
		{			
			cout << timeVector.at(i)->ToString() << endl;
		}

		for (int k = 0; k < timeVector.size(); k++)
		{
			delete timeVector.at(k);
		}

	}
	catch (exception e) {
		cerr << e.what() << endl;
	}	

	return 0;
}