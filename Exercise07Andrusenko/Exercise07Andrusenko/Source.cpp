#include "Address.h"
#include "Date.h"
#include "Person.h"


#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

const int n = 3;
const string txtFile = "people.txt";
const string binFile = "people.bin";


void save() {
	Person people[n];

	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		int day = rand() % 30 + 1;
		int month = rand() % 12 + 1;
		int year = rand() % 20 + 1980;
		int zip = rand() % 50000 + 10000;
		Date dob{ day, month, year };
		Address add{ "street" + to_string(i), "city" + to_string(i), zip };
		Person p{ "Firstname" + to_string(i), "Lastname" + to_string(i), add, dob };
		people[i] = p;
	}

	ofstream write;
	write.open(txtFile);
	for (int i = 0; i < n; i++) {
		write << people[i] << std::endl;
	}
	write.close();
}

Person* load() {
	cout << txtFile << endl;
	int numberOfLines = 0;
	std::string line;
	std::ifstream read(txtFile);

	while (std::getline(read, line))
		++numberOfLines;

	read.clear();
	read.seekg(0);

	Person* people = new Person[numberOfLines];	
	for (int i = 0; i < numberOfLines; i++) {
		std::getline(read, line);
		std::istringstream stream(line);		
		stream >> people[i];		
	}

	read.close();

	return people;	
}

void saveBin() {
	Person people[n];

	for (int i = 0; i < n; i++)
	{
		int day = rand() % 30 + 1;
		int month = rand() % 12 + 1;
		int year = rand() % 20 + 1980;
		int zip = rand() % 50000 + 10000;
		Date dob{ day, month, year };
		Address add{ "street" + to_string(i), "city" + to_string(i), zip };
		Person p{ "Firstname" + to_string(i), "Lastname" + to_string(i), add, dob };
		people[i] = p;
	}

	ofstream output;
	output.open(binFile, ios::out | ios::binary);
	output.write((const char*)&people, sizeof(people));

	output.close();


}

Person* loadBin() {
	cout << binFile << endl;
	std::ifstream readFile(binFile, std::ios::out | std::ios::binary);
	Person* people = new Person[n];
	for (int i = 0; i < n; i++)
	{
		readFile.read((char*)&people[i], sizeof(Person));
	}		
	readFile.close();
	return people;
}


int main(int argc, char* argv)
{	 	 
	try
	{
		save();
		Person* people1 = load();
		for (int i = 0; i < n; i++)
		{
			cout << people1[i] << endl;
		}		

		saveBin();
		Person* people2 = loadBin();
		for (int i = 0; i < n; i++)
		{
			cout << people2[i] << endl;
		}				
	}
	catch (const exception& e)
	{		
		cerr << e.what() << endl;
	}

	
	
	return 0;
}


