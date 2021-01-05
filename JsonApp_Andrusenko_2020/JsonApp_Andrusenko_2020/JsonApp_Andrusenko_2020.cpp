#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <api.h>
#include <sstream>

#include "Student.h"
#include "Subject.h"

using namespace std;

void menuHelp()
{
	cout << "===========================================================================" << endl;
	cout << "List of commands: " << endl;
	cout << "\"help\"			 - to print list of commands" << endl;
	cout << "\"print-students\"	 - print students as json" << endl;
	cout << "\"print-subjects\"	 - print subjects as json" << endl;
	cout << "\"add-student\"		 - add new student" << endl;
	cout << "\"edit-student\"		 - edite student" << endl;
	cout << "\"delete-student\"	 - delete student" << endl;
	cout << "\"add-sub-to-stud\"	 - add subject to student" << endl;
	cout << "\"del-sub-from-stud\"	 - delete subject to student" << endl;
	cout << "\"add-subject\"		 - add new subject" << endl;
	cout << "\"edit-subject\"		 - edite subject" << endl;
	cout << "\"delete-subject\"	 - delete subject" << endl;
	cout << "\"exit\"			 - save all data and exit" << endl;
	cout << "===========================================================================" << endl;
}

ObjectValue* createObjectValue(DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects) {
	ObjectValue* result = new ObjectValue;
	ArrayValue* arrayStudents = new ArrayValue;
	ArrayValue* arraySubjects = new ArrayValue;
	for (int i = 0; i < daStudents->getSize(); i++)
	{
		arrayStudents->append(daStudents->getElementAt(i)->deserialize());
	}

	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		arraySubjects->append(daSubjects->getElementAt(i)->deserialize());
	}
	result->append(KeyValuePair{ "students", arrayStudents });
	result->append(KeyValuePair{ "subjects", arraySubjects });
	return result;
}

bool studentExists(int id, DynamicArray<Student*>* daStudents)
{
	for (int i = 0; i < daStudents->getSize(); i++)
	{
		if (daStudents->getElementAt(i)->getId() == id)
		{
			return true;
		}
	}
	return false;
}

bool subjectExists(int id, DynamicArray<Subject*>* daSubjects)
{
	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		if (daSubjects->getElementAt(i)->getId() == id)
		{
			return true;
		}
	}
	return false;
}

Student* findStudent(int id, DynamicArray<Student*>* daStudents)
{
	for (int i = 0; i < daStudents->getSize(); i++)
	{
		if (daStudents->getElementAt(i)->getId() == id)
		{
			return daStudents->getElementAt(i);
		}
	}
	throw out_of_range("Student with given id was not found.");
}

Student* createStudent(int id, string firstname, string lastname, string gender, Date dob)
{
	ostringstream oss1;
	ostringstream oss2;
	ostringstream oss3;
	JSON::escape(firstname, oss1);
	JSON::escape(lastname, oss2);
	JSON::escape(gender, oss3);
	return new Student(id, oss1.str(), oss2.str(), oss3.str(), dob);
}

void deleteStudent(int id, DynamicArray<Student*>* daStudents)
{
	if (!studentExists(id, daStudents))
	{
		ostringstream oss;
		oss << "Student with id -";
		oss << id;
		oss << "- does not exist.";
		throw out_of_range(oss.str());
	}

	for (int i = 0; i < daStudents->getSize(); i++)
	{
		Student* tmp = daStudents->getElementAt(i);
		if (tmp->getId() == id)
		{
			daStudents->deleteAtIndex(i);
			delete tmp;
			break;
		}
	}
}

Subject* createSubject(int id, string name)
{
	ostringstream oss;
	JSON::escape(name, oss);
	return new Subject(id, oss.str());
}

void deleteSubject(int id, DynamicArray<Subject*>* daSubjects, DynamicArray<Student*>* daStudents)
{
	if (!subjectExists(id, daSubjects))
	{
		ostringstream oss;
		oss << "Subject with id -";
		oss << id;
		oss << "- does not exist.";
		throw out_of_range(oss.str());
	}

	for (int i = 0; i < daStudents->getSize(); i++)
	{
		daStudents->getElementAt(i)->DeleteSubjectId(id);
	}

	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		Subject* tmp = daSubjects->getElementAt(i);
		if (tmp->getId() == id)
		{
			daSubjects->deleteAtIndex(i);
			delete tmp;
			break;
		}
	}
}

void menuPrintStudents(DynamicArray<Student*>* daStudents)
{
	for (int i = 0; i < daStudents->getSize(); i++)
	{
		ObjectValue* tempStud = daStudents->getElementAt(i)->deserialize();
		cout << JSON::serialize(tempStud) << endl;
		delete tempStud;
	}
}

void menuPrintSubjects(DynamicArray<Subject*>* daSubjects)
{
	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		ObjectValue* tempSub = daSubjects->getElementAt(i)->deserialize();
		cout << JSON::serialize(tempSub) << endl;
		delete tempSub;
	}
}

void menuAddStudent(DynamicArray<Student*>* daStudents)
{
	try
	{
		int id = 0;
		cout << "Please enter id:";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		if (studentExists(id, daStudents))
		{
			ostringstream oss;
			oss << "Student with id -";
			oss << id;
			oss << "- already exists.";
			cout << oss.str() << endl;
			return;
		}

		string firstname;
		cout << "Please enter firstname:";
		getline(cin >> ws, firstname);

		string lastname;
		cout << "Please enter lastname:";
		getline(cin >> ws, lastname);

		string gender;
		cout << "Please enter gender:";
		getline(cin >> ws, gender);

		cout << "Please enter your birth date." << endl;
		int day = 0;
		cout << "Please enter day:";
		cin >> day;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		int month = 0;
		cout << "Please enter month:";
		cin >> month;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		int year = 0;
		cout << "Please enter year:";
		cin >> year;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		Date dob{ day, month, year };

		daStudents->append(createStudent(id, firstname, lastname, gender, dob));
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void menuDeleteStudent(DynamicArray<Student*>* daStudents)
{
	try
	{
		int id = 0;
		cout << "Please enter id of student you want to delete: ";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		deleteStudent(id, daStudents);
		cout << "Student has been deleted." << endl;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void menuAddSubToStud(DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects)
{
	try
	{
		int idStud = 0;
		cout << "Please enter id of student: ";
		cin >> idStud;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		if (!studentExists(idStud, daStudents))
		{
			ostringstream oss;
			oss << "Student with id -";
			oss << idStud;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}

		int idSub = 0;
		cout << "Please enter id of subject: ";
		cin >> idSub;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		if (!subjectExists(idSub, daSubjects))
		{
			ostringstream oss;
			oss << "Subject with id -";
			oss << idSub;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}

		Student* tempSt = findStudent(idStud, daStudents);
		tempSt->AddSubjectId(idSub);
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void menuDelSubFromStud(DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects)
{
	try
	{
		int idStud = 0;
		cout << "Please enter id of student: ";
		cin >> idStud;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		if (!studentExists(idStud, daStudents))
		{
			ostringstream oss;
			oss << "Student with id -";
			oss << idStud;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}

		int idSub = 0;
		cout << "Please enter id of subject: ";
		cin >> idSub;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		if (!subjectExists(idSub, daSubjects))
		{
			ostringstream oss;
			oss << "Subject with id -";
			oss << idSub;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}

		Student* tempSt = findStudent(idStud, daStudents);
		tempSt->DeleteSubjectId(idSub);
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void manuAddSubject(DynamicArray<Subject*>* daSubjects)
{
	try
	{
		int id = 0;
		cout << "Please enter id:";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		if (subjectExists(id, daSubjects))
		{
			ostringstream oss;
			oss << "Subject with id -";
			oss << id;
			oss << "- already exists.";
			cout << oss.str() << endl;
			return;
		}

		string name;
		cout << "Please enter name:";
		getline(cin >> ws, name);

		daSubjects->append(createSubject(id, name));
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void menuDeleteSubject(DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects)
{
	try
	{
		int id = 0;
		cout << "Please enter id of subject you want to delete: ";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
		deleteSubject(id, daSubjects, daStudents);
		cout << "Subject has been deleted." << endl;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void menuExit(DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects)
{
	cout << "Saving data to students.json..." << endl;
	ObjectValue* temp = createObjectValue(daStudents, daSubjects);
	ofstream out("students.json");
	string jsonStr(JSON::serialize(temp));
	cout << jsonStr << endl;
	if (out.is_open())
	{
		out << jsonStr;
	}
	else
	{
		throw exception("File exception.");
	}
	out.close();
	delete temp;

	for (int i = 0; i < daStudents->getSize(); i++)
	{
		delete daStudents->getElementAt(i);
	}
	delete daStudents;

	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		delete daSubjects->getElementAt(i);
	}
	delete daSubjects;
	cout << "Exiting..." << endl;
}

void loadFile(string filename, DynamicArray<Student*>* daStudents, DynamicArray<Subject*>* daSubjects)
{
	ObjectValue* fullJson = nullptr;
	ifstream in(filename);
	string jsonStr;
	if (in.is_open())
	{
		ostringstream oss;
		while (getline(in, jsonStr))
		{
			oss << jsonStr;
			cout << jsonStr << endl;
		}
		jsonStr = oss.str();
	}
	else
	{
		throw exception("File exception");
	}
	in.close();

	if (!(fullJson = dynamic_cast<ObjectValue*>(JSON::deserialize(jsonStr))))
	{
		throw invalid_argument("students.json is empty or corrupted.");
	}

	ArrayValue* students = dynamic_cast<ArrayValue*>(JSON::getValueByKey("students", fullJson));
	ArrayValue* subjects = dynamic_cast<ArrayValue*>(JSON::getValueByKey("subjects", fullJson));

	for (int i = 0; i < students->getValues()->getSize(); i++)
	{
		daStudents->append(new Student{ dynamic_cast<ObjectValue*>(students->getValues()->getElementAt(i)) });
	}
	for (int i = 0; i < subjects->getValues()->getSize(); i++)
	{
		daSubjects->append(new Subject{ dynamic_cast<ObjectValue*>(subjects->getValues()->getElementAt(i)) });
	}
	delete fullJson;
}

void menuEditStudent(DynamicArray<Student*>* daStudents)
{
	try
	{
		int id = 0;
		cout << "Please enter id of student:";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		if (studentExists(id, daStudents))
		{
			Student* tempSt = findStudent(id, daStudents);
			do
			{
				string field;
				cout << "Student fields: \"firstname\", \"lastname\", \"gender\", \"dateofbirth\". Type \"cancel\" to cancel editing." << endl;
				cout << "Please enter field's name you want to edit:";
				getline(cin >> ws, field);
				if (cin.fail())
				{
					cout << "ERROR -- unexpected error." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}

				if (field == "firstname")
				{
					string firstname;
					cout << "Please enter new firstname:";
					getline(cin >> ws, firstname);
					tempSt->setFirstname(firstname);
				}
				else if (field == "lastname")
				{
					string lastname;
					cout << "Please enter new lastname:";
					getline(cin >> ws, lastname);
					tempSt->setLastname(lastname);
				}
				else if (field == "gender")
				{
					string gender;
					cout << "Please enter new gender:";
					getline(cin >> ws, gender);
					tempSt->setGender(gender);
				}
				else if (field == "dateofbirth")
				{
					int day = 0;
					cout << "Please enter day:";
					cin >> day;
					if (cin.fail())
					{
						cout << "ERROR -- You did not enter an integer" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}

					int month = 0;
					cout << "Please enter month:";
					cin >> month;
					if (cin.fail())
					{
						cout << "ERROR -- You did not enter an integer" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}

					int year = 0;
					cout << "Please enter year:";
					cin >> year;
					if (cin.fail())
					{
						cout << "ERROR -- You did not enter an integer" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					tempSt->setDateOfBirth(Date{ day, month, year });
				}
				else if (field == "cancel")
				{
					return;
				}
				else
				{
					cout << "Unknown command. Please try again." << endl;
				}
			} while (true);
		}
		else
		{
			ostringstream oss;
			oss << "Student with id -";
			oss << id;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}
	}
	catch (const std::exception& ex)
	{
		cout << "EROR -- canceling editing." << endl;
		cerr << ex.what() << endl;
	}
}

Subject* findSubject(int id, DynamicArray<Subject*>* daSubjects)
{
	for (int i = 0; i < daSubjects->getSize(); i++)
	{
		if (daSubjects->getElementAt(i)->getId() == id)
		{
			return daSubjects->getElementAt(i);
		}
	}
	throw out_of_range("Subject with given id was not found.");
}

void menuEditSubject(DynamicArray<Subject*>* daSubjects)
{
	try
	{
		int id = 0;
		cout << "Please enter id of subject:";
		cin >> id;
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an integer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}

		if (subjectExists(id, daSubjects))
		{
			Subject* tempSub = findSubject(id, daSubjects);
			do
			{
				string field;
				cout << "Subject fields: \"name\". Type \"cancel\" to cancel editing." << endl;
				cout << "Please enter field's name you want to edit:";
				cin >> field;
				if (cin.fail())
				{
					cout << "ERROR -- unexpected error." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}

				if (field == "name")
				{
					string name;
					cout << "Please enter new name:";
					getline(cin >> ws, name);
					tempSub->setName(name);
				}
				else if (field == "cancel")
				{
					return;
				}
				else
				{
					cout << "Unknown command. Please try again." << endl;
				}
			} while (true);
		}
		else
		{
			ostringstream oss;
			oss << "Subject with id -";
			oss << id;
			oss << "- does not exist.";
			cout << oss.str() << endl;
			return;
		}
	}
	catch (const std::exception& ex)
	{
		cout << "EROR -- canceling editing." << endl;
		cerr << ex.what() << endl;
	}
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		DynamicArray<Student*>* daStudents = new DynamicArray<Student*>;
		DynamicArray<Subject*>* daSubjects = new DynamicArray<Subject*>;
		loadFile("students.json", daStudents, daSubjects);
		menuHelp();
		do
		{
			string input;
			cout << endl << "Please enter command: ";
			getline(cin >> ws, input);

			if (input == "help")
			{
				menuHelp();
			}
			else if (input == "print-students")
			{
				menuPrintStudents(daStudents);
			}
			else if (input == "print-subjects")
			{
				menuPrintSubjects(daSubjects);
			}
			else if (input == "add-student")
			{
				menuAddStudent(daStudents);
			}
			else if (input == "delete-student")
			{
				menuDeleteStudent(daStudents);
			}
			else if (input == "edit-student")
			{
				menuEditStudent(daStudents);
			}
			else if (input == "add-sub-to-stud")
			{
				menuAddSubToStud(daStudents, daSubjects);
			}
			else if (input == "del-sub-from-stud")
			{
				menuDelSubFromStud(daStudents, daSubjects);
			}
			else if (input == "add-subject")
			{
				manuAddSubject(daSubjects);
			}
			else if (input == "edit-subject")
			{
				menuEditSubject(daSubjects);
			}
			else if (input == "delete-subject")
			{
				menuDeleteSubject(daStudents, daSubjects);
			}
			else if (input == "exit")
			{
				menuExit(daStudents, daSubjects);
				break;
			}
			else
			{
				cout << "Unknown command. Please type \"help\" to print list of commands." << endl;
			}
		} while (true);
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}