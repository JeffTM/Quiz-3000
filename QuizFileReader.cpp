#include "QuizFileReader.h"
using namespace std;

QuizFileReader::QuizFileReader()
	:path("quiz.txt")
{}

QuizFileReader::QuizFileReader(const char * filePath)
	:path(filePath)
{}

QuizFileReader::QuizFileReader(const std::string & filePath)
	:path(filePath)
{}

void QuizFileReader::setPath(const char * filePath)
{
	path = filePath;
}

void QuizFileReader::setPath(const std::string & filePath)
{
	path = filePath;
}

string QuizFileReader::getPath() const
{
	return path;
}

bool QuizFileReader::checkFile() const
{
	bool result;
	ifstream fin(path);
	result = fin.good();
	fin.close();
	return result;
}

void QuizFileReader::read(Jeff::Vector<shared_ptr<Question>> & v)
{
	string fileContents;
	loadFileContents(fileContents);
	size_t pos = 0; //Current read position
	
	pos = findTag("quiz", fileContents, pos); //Find the opening quiz tag

	string nextTag;
	while ((nextTag = nextQuestionTag(fileContents, pos)) != "") //While there a still question tags in fileContents
	{
		pos = findTag(nextTag, fileContents, pos); //Advance past the question tag

		//Read the prompt
		string prompt;
		size_t promptEndPos;
		pos = findTag("prompt", fileContents, pos); //Find the prompt tag and advance past it
		promptEndPos = findEndTagNoOff("prompt", fileContents, pos);
		prompt = fileContents.substr(pos, promptEndPos - pos);
		trim(prompt);
		pos = findEndTag("prompt", fileContents, pos); //Advance past the prompt end tag

		//Read the number of points
		int numPoints;
		size_t pointsEndPos;
		string pointsString;
		pos = findTag("points", fileContents, pos); //Find the points tag and advance past it
		pointsEndPos = findEndTagNoOff("points", fileContents, pos);
		pointsString = fileContents.substr(pos, pointsEndPos - pos);
		trim(pointsString);
		numPoints = stoi(pointsString);
		pos = findEndTag("points", fileContents, pos); //Advance past the points end tag

		//If this is a free response question add it to the vector
		if (nextTag == "question_fr")
		{
			v.add(shared_ptr<Question>(new FRQuestion(prompt, numPoints)));
		}
		else
		{
			if (nextTag == "question_tf") //If the question is a true false question
			{
				bool answer;
				size_t answerEndPos;
				string answerString;
				pos = findTag("answer", fileContents, pos); //Find the answer tag and advance past it
				answerEndPos = findEndTagNoOff("answer", fileContents, pos);
				answerString = fileContents.substr(pos, answerEndPos - pos);
				trim(answerString);
				answer = stringToBool(answerString);
				pos = findEndTag("answer", fileContents, pos); //Advance past the answer end tag

				v.add(shared_ptr<Question>(new TFQuestion(prompt, numPoints, answer)));
			}
			else //It must be a multiple choice question
			{
				string answer;
				size_t answerEndPos;
				pos = findTag("answer", fileContents, pos); //Find the answer tag and advance past it
				answerEndPos = findEndTagNoOff("answer", fileContents, pos);
				answer = fileContents.substr(pos, answerEndPos - pos);
				trim(answer);
				pos = findEndTag("answer", fileContents, pos); //Advance past the answer end tag

				v.add(shared_ptr<Question>(new MCQuestion(prompt, numPoints, answer)));
			}
		}

		pos = findEndTag(nextTag, fileContents, pos); //Advance past the question end tag
	}

	findEndTag("quiz", fileContents, pos); //Make sure the quiz end tag exists
}

//private -----------------------------------------------

void QuizFileReader::loadFileContents(string & fileContents)
{
	ifstream fin(path);

	if (fin.good())
	{
		//Create a dynamic array to store the contents of the file
		int length = fileLength(fin);
		char * temp = new char[length];
		fin.read(temp, length);
		fileContents = temp;
		delete[] temp;
	}
	else
		throw FileNotFoundException("The file could not be read");

	fin.close();
}

int QuizFileReader::fileLength(ifstream & file)
{
	int length;
	file.seekg(0, ios::end);
	length = static_cast<int>(file.tellg());
	file.seekg(0, ios::beg);
	return length;
}

size_t QuizFileReader::findTag(const string & name, const string & data, size_t pos)
{
	size_t findResult = data.find('<' + name + '>', pos);
	if (findResult == string::npos)
		throw InvalidQuizException("Could not find tag <" + name + '>');
	return findResult + name.length() + 2;
}

size_t QuizFileReader::findEndTag(const string & name, const string & data, size_t pos)
{
	return findTag('/' + name, data, pos);
}

size_t QuizFileReader::findEndTagNoOff(const string & name, const string & data, size_t pos)
{
	size_t findResult = data.find("</" + name + '>', pos);
	if (findResult == string::npos)
		throw InvalidQuizException("Could not find tag </" + name + '>');
	return findResult;
}

string QuizFileReader::nextQuestionTag(const string & data, size_t pos)
{
	string validTags[3] = { "question_fr", "question_mc", "question_tf" };
	int resultID = -1;
	size_t resultPos = string::npos;

	for (int i = 0; i < 3; i++)
	{
		size_t tagPos = data.find('<' + validTags[i] + '>', pos);
		if (tagPos != string::npos && tagPos < resultPos)
		{
			resultPos = tagPos;
			resultID = i;
		}
	}

	if (resultPos == string::npos)
		return string();
	else
		return validTags[resultID];
}

void QuizFileReader::trim(string & s)
{
	string whitespace = " \f\n\r\t\v";
	size_t first = s.find_first_not_of(whitespace);
	size_t last = s.find_last_not_of(whitespace);

	if (first == string::npos) //If all the characters where whitespace
		s.clear();
	else
		s = s.substr(first, (last - first + 1));
}

bool QuizFileReader::stringToBool(string s)
{
	//Convert s to lowercase
	for (size_t i = 0; i < s.length(); i++)
		s[i] = (char) (tolower(s[i]));
	return (s == "true") || (s == "t");
}
