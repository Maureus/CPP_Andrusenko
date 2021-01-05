#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <api.h>

class Subject
{
	int id;
	std::string name;
public:
	Subject() = default;
	Subject(ObjectValue* object);
	Subject(int id, std::string name);
	~Subject() = default;
	ObjectValue* deserialize() const;
	int getId() const;
	void setName(std::string name);
};

#endif // !SUBJECT_H