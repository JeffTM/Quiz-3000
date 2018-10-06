#include "InvalidQuizException.h"
using namespace std;

InvalidQuizException::InvalidQuizException()
	:runtime_error("InvalidQuizException")
{}

InvalidQuizException::InvalidQuizException(const char * mess)
	: runtime_error(mess)
{}

InvalidQuizException::InvalidQuizException(const string & mess)
	: runtime_error(mess)
{}
