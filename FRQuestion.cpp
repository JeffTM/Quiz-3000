#include "FRQuestion.h"
using namespace std;

FRQuestion::FRQuestion()
	:Question()
{}

FRQuestion::FRQuestion(const string & prompt, int points)
	:Question(prompt, points)
{}

int FRQuestion::scoreAnswer(string answer, ostream & output)
{
	output << "Prompt:" << endl;
	displayPrompt(output);
	output << "Answer:" << endl;
	output << answer << endl;
	return 0;
}
