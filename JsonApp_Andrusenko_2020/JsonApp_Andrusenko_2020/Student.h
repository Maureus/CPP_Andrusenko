#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <api.h>
#include "Subject.h"
#include "Date.h"

class Student
{
	int id;
	std::string firstname;
	std::string lastname;
	std::string gender;
	Date dateofbirth;
	DynamicArray<int> subjects{};
public:
	Student() = default;
	Student(ObjectValue* object);
	Student(int id, std::string firstname, std::string lastname, std::string gender, Date dateofbirth);
	~Student() = default;
	void AddSubjectId(int id);
	void DeleteSubjectId(int id);
	ObjectValue* deserialize() const;
	int getId() const;
	void setFirstname(std::string firstname);
	void setLastname(std::string lastname);
	void setGender(std::string gender);
	void setDateOfBirth(Date dob);
};

#endif // !STUDENT_H
