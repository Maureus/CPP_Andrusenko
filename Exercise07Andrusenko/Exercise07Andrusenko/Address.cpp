#include "Address.h"
#include <stdexcept>

using namespace std;

Address::Address()
{
}

Address::Address(const std::string& street, const std::string& city, const int& zip)
{
	if (street.empty() || city.empty() || zip <= 0) {
		throw invalid_argument("Unaceptable address!");
	}

	this->street = street;
	this->city = city;
	this->zip = zip;
}

Address::~Address()
{
}

std::ostream& operator<<(std::ostream& os, const Address& address)
{
	os << address.street << " " << address.city << " " << address.zip;
	return os;
}

std::istream& operator>>(std::istream& is, Address& address)
{		
	is >> address.street >> address.city >> address.zip;
	return is;
}
