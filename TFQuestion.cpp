#include "TFQuestion.h"
using namespace std;

TFQuestion::TFQuestion()
	:Question(), correctAnswer()
{}

TFQuestion::TFQuestion(const string & prompt, int points, bool correctAnswer)
	: Question(prompt, points), correctAnswer(correctAnswer)
{}

void TFQuestion::displayPrompt(std::ostream & output)
{
	output << "True or false: ";
	Question::displayPrompt(output);
}

int TFQuestion::scoreAnswer(string answer, ostream & output)
{
	toLowerCase(answer);

	if ((correctAnswer && (answer == "true" || answer == "t"))
		 || (!correctAnswer && (answer == "false" || answer == "f")))
	{
		output << "Correct! " << endl;
		return getPoints();
	}
	else
	{
		output << "Incorrect. The correct answer was: ";
		if (correctAnswer)
			output << "true";
		else
			output << "false";
		output << endl;
		return 0;
	}
}
