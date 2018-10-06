#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class InvalidQuizException : public std::runtime_error
{
public:
	InvalidQuizException();
	InvalidQuizException(const char * mess);
	InvalidQuizException(const std::string & mess);
};
