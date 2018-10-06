#include "MCQuestion.h"
using namespace std;

MCQuestion::MCQuestion()
	:Question(), correctAnswer()
{}

MCQuestion::MCQuestion(const string & prompt, int points, string correctAns)
	:Question(prompt, points), correctAnswer()
{
	toLowerCase(correctAns);
	correctAnswer = correctAns;
}

int MCQuestion::scoreAnswer(string answer, ostream & output)
{
	toLowerCase(answer);

	if (answer == correctAnswer)
	{
		output << "Correct! " << endl;
		return getPoints();
	}
	else
	{
		output << "Incorrect. The correct answer was: " << correctAnswer << endl;
		return 0;
	}
}
