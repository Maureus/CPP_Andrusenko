#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

int main(int argc, char* argv)
{
	try {
		int n = 10;
		vector<Time*> timeVector (n);
		for (int i = 0; i < n; i++)
		{
			timeVector.at(i) = new Time(rand() % 25, rand() % 60, rand() % 60);			
		}

		int i, j, minIndx;
		 
		for (i = 0; i < n - 1; i++)
		{			 
			minIndx = i;
			for (j = i + 1; j < n; j++)
				if(timeVector.at(j)->CompareTo(timeVector.at(minIndx)) == -1)				
					minIndx = j;
			
			Time* temp = timeVector.at(minIndx);
			timeVector.at(minIndx) = timeVector.at(i);
			timeVector.at(i) = temp;
		}

		for (int k = 0; k < timeVector.size(); k++)
		{
			cout << timeVector.at(k)->ToString() << endl;
		}


		Time t1 = Time(9, 47, 40);
		Time t2 = Time(11, 27, 1);				
		cout << t1.ToString() << endl;
		cout << t2.ToString() << endl;
		cout << t1.CompareTo(&t2) << endl;

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