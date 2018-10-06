#include "Question.h"
using namespace std;

Question::Question()
	:prompt(), points(0)
{}

Question::Question(const string & prompt, int points)
	:prompt(prompt), points(points)
{}

Question::~Question()
{}

void Question::displayPrompt(std::ostream & output)
{
	output << prompt << endl;
}

int Question::getPoints()
{
	return points;
}

void Question::toLowerCase(string & s)
{
	for (size_t i = 0; i < s.length(); i++)
		s[i] = (char)(tolower(s[i]));
}
