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


void writeTxt() {
	cout << "Writing " << txtFile << endl;

	srand(time(NULL));	

	ofstream write;
	write.open(txtFile);
	if (write.is_open())
	{
		for (int i = 0; i < n; i++) {
			int day = rand() % 30 + 1;
			int month = rand() % 12 + 1;
			int year = rand() % 20 + 1980;
			int zip = rand() % 50000 + 10000;
			Date dob{ day, month, year };
			Address lta{ "street" + to_string(i), "city" + to_string(i), zip };
			Person p{ "Firstname" + to_string(i), "Lastname" + to_string(i), lta, dob };			
			write << p << std::endl;
		}
		write.close();
	}	
}

Person* readTxt() {
	cout << "Reading " << txtFile << endl;
	int numberOfLines = 0;
	string line;
	ifstream read(txtFile);

	if (read.is_open())
	{
		while (getline(read, line))
		{
			numberOfLines++;
		}

		read.clear();
		read.seekg(0);

		Person* people = new Person[numberOfLines];
		for (int i = 0; i < numberOfLines; i++) {
			getline(read, line);
			istringstream stream(line);
			stream >> people[i];
		}

		read.close();
		return people;
	}

	return nullptr;
}

void writeBin() {
	cout << "Writing " << binFile << endl;
	Person people[n];
	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		int day = rand() % 30 + 1;
		int month = rand() % 12 + 1;
		int year = rand() % 20 + 1980;
		int zip = rand() % 50000 + 10000;
		Date dob{ day, month, year };
		Address lta{ "street" + to_string(i), "city" + to_string(i), zip };
		Person p{ "Firstname" + to_string(i), "Lastname" + to_string(i), lta, dob };
		people[i] = p;
	}

	ofstream writeFile(binFile, ios::binary);
	if (writeFile.is_open())
	{
		writeFile.write((const char*)&people, sizeof(people));
		writeFile.close();
	}
}

Person* readBin() {
	cout << "Reading "<< binFile << endl;

	ifstream readFile(binFile, ios::binary);
	Person* people = new Person[n];
	if (readFile.is_open())
	{		
		for (int i = 0; i < n; i++)
		{
			readFile.read((char*)&people[i], sizeof(Person));
		}
		readFile.close();

		return people;
	}
	
	return nullptr;
}


int main(int argc, char* argv)
{	 	 
	try
	{
		writeTxt();
		Person* people1 = readTxt();
		for (int i = 0; i < n; i++)
		{
			cout << people1[i] << endl;
		}		

		writeBin();
		Person* people2 = readBin();
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


