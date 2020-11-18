#pragma once
#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
#include <string>

class Address
{
	std::string street;
	std::string city;
	int zip;
public:
	Address();
	Address(const std::string& street, const std::string& city, const int& zip);
	~Address();	
	friend std::ostream& operator<<(std::ostream& os, const Address& address);
	friend std::istream& operator>>(std::istream& is, Address& address);
};

#endif // !ADDRESS_H



