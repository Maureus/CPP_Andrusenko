#ifndef OBJECT_H
#define OBJECT_H

class Object
{
protected:
	int id;
	double x;
	double y;
public:
	Object(int);
	virtual ~Object();
	void SetX(double);
	void SetY(double);
	int GetId() const;
	double GetX() const;
	double GetY() const;
};

#endif // !OBJECT_H