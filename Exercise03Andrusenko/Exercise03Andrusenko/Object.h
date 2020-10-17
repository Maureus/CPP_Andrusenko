#pragma once
class Object
{
protected:
	int id;
	double x;
	double y;
public:
	Object();
	Object(int);
	virtual ~Object();
	void SetX(double);
	void SetY(double);
	int GetId() const;
	double GetX() const;
	double GetY() const;
};

