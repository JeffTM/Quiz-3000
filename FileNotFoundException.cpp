#include "FileNotFoundException.h"
using namespace std;

FileNotFoundException::FileNotFoundException()
	:runtime_error("FileNotFoundException")
{}

FileNotFoundException::FileNotFoundException(const char * mess)
	: runtime_error(mess)
{}

FileNotFoundException::FileNotFoundException(const string & mess)
	: runtime_error(mess)
{}
