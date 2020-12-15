#include "Array2D.h"
#include <iostream>

int main(int atgv,  char* argc) 
{
	try
	{
		//Array2D<char> test{ 3,3 };
		Array2D<int> m{ 3,3 };
		int jednodpole[] = { 0,1,2,3,4,5,6,7,8 };
		m.PutFrom(jednodpole);
		Array2D<int> mt = m.Transpose();
		Array2D<int> mmt = m.Multiplication(mt);
		Array2D<double> mmt_d = mmt.Cast<double>();
		Array2D<double> n_d{ 3,3 };
		double jednodpole_d[] = { 4.5,5,0,2,-0.5,7,1.5,9,6 };
		n_d.PutFrom(jednodpole_d);
		Array2D<double> mmtn_d = mmt_d.Multiplication(n_d);
		Array2D<int> r = mmtn_d.Cast<int>();
		Array2D<int> t{ 3,3 };
		int tpole[] = { 85,225,236,292,819,866,499,1413,1496 };
		t.PutFrom(tpole);
		r.Print();
		t.Print();
		std::cout << "r==t ? " << (r.IsEqual(t) ? "true" : "false") << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	

	return 0;
}