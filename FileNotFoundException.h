#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException();
	FileNotFoundException(const char * mess);
	FileNotFoundException(const std::string & mess);
};
