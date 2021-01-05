#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include <stdexcept>
#include <string>

class JsonException : public std::exception
{
	std::string message;
public:
	explicit JsonException(const std::string& msg);
	const char* what() const throw();
};

#endif // !JSON_EXCEPTION_H