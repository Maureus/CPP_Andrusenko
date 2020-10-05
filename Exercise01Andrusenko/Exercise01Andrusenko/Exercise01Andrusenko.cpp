#include <iostream>

struct Trojuhelnik {
	int a;
	int b;
	int c;
};

bool lzeSestrojit(Trojuhelnik t) {
	if (t.a + t.b > t.c && t.a + t.c > t.b && t.b + t.c > t.a)
	{
		return true;
	}

	return false;
}

bool lzeSestojitPtr(Trojuhelnik* t) {
	if (t->a + t->b > t->c && t->a + t->c > t->b && t->b + t->c > t->a)
	{
		return true;
	}

	return false;
}

int main()
{
	int number;
	std::cout << "Please enter number of triangles you want to create: ";
	std::cin >> number;

	Trojuhelnik* ukazatel = new Trojuhelnik[number];	

	for (int i = 0; i < number; i++)
	{
		std::cout << "Please enter size a: ";
		std::cin >> ukazatel[i].a;
		std::cout << "Please enter size b: ";
		std::cin >> ukazatel[i].b;
		std::cout << "Please enter size c: ";
		std::cin >> ukazatel[i].c;		
		
		if (lzeSestojitPtr(&ukazatel[i]))
		{			
			int p = ukazatel[i].a + ukazatel[i].b + ukazatel[i].c;
			std::cout << "Perimetr of triangle is: " << p << std::endl;
		}
		else
			std::cout << "Triangle with this sizes couldn't exist\n";
	}		
	
	delete[] ukazatel;	
}