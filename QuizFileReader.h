#pragma once
#include <fstream>
#include <memory>
#include <string>
#include "FileNotFoundException.h"
#include "FRQuestion.h"
#include "InvalidQuizException.h"
#include "MCQuestion.h"
#include "Question.h"
#include "TFQuestion.h"
#include "Vector.h"

class QuizFileReader
{
public:
	//Default Constructor, assumes the file path is "quiz.txt"
	QuizFileReader();
	//Constructor, sets the file path
	QuizFileReader(const char * filePath);
	QuizFileReader(const std::string & filePath);

	//Sets the file path
	void setPath(const char * filePath);
	void setPath(const std::string & filePath);
	//Gets  the file path
	std::string getPath() const;
	//Returns true if the file at path exists. Does not check if the file will be successfuly read by read()
	bool checkFile() const;
	//Attempts to read the file and process it into a vector of shared pointers to question objects. Throws an InvalidQuizException if the file cannot be read.
	void read(Jeff::Vector<std::shared_ptr<Question>> & v);

private:
	//Stores the file path to be read from
	std::string path;

	//File helper methods
	// Reads the entire file and stores its contents fileContents
	void loadFileContents(std::string & fileContents);
	//Gets the length of the file currently open in the ifstream
	int fileLength(std::ifstream & file);

	//Read helper methods
	//Looks for the tag <name> in data starting at pos and throws an InvalidQuizException if it is not found. Returns the location of the first character after the tag as a size_t.
	size_t findTag(const std::string & name, const std::string & data, size_t pos);
	//Looks for the tag </name> in data starting at pos and throws an InvalidQuizException if it is not found. Returns the location of the first character after the tag as a size_t.
	size_t findEndTag(const std::string & name, const std::string & data, size_t pos);
	//Looks for the tag </name> in data starting at pos and throws an InvalidQuizException if it is not found. Returns the location of the first character of the tag as a size_t.
	size_t findEndTagNoOff(const std::string & name, const std::string & data, size_t pos);
	//Looks for the next valid question tag in the data starting at pos and returns the tag without <> as a string. An empty string is returned if no tags are found.
	std::string nextQuestionTag(const std::string & data, size_t pos);

	//String manipulation helper methods
	//Removes the leading and trailing whitespace characters from s
	void trim(std::string & s);
	//Returns the boolean value represented by s. "true" and "t" are considered true while anything else is considered false. Ignores case
	bool stringToBool(std::string s);
};
